#include "nanoai/runtime.h"
#include "backend.h"
#include "backends/onnx_backend.h"
#include "backends/tflite_backend.h"
#include "backends/gguf_backend.h"
#include "backends/openvino_backend.h"
#include "backends/pytorch_backend.h"
#include "acceleration/selector.h"
#include "memory/optimizer.h"
#include "conversion/converter.h"
#include "networking/network_manager.h"
#include "service/os_service.h"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <chrono>

namespace nanoai {

class NanoRuntime::Impl {
public:
    Impl() {}
    ~Impl() {}

    bool loadModel(const std::string& modelPath, const std::string& modelId, ModelFormat format) {
        if (format == ModelFormat::AUTO) {
            format = detectFormat(modelPath);
        }

        MemoryOptimizer::applyOptimizations(modelPath);

        DeviceType device = SmartRuntimeSelector::selectBestDevice();
        std::cout << "Runtime: Distributing model " << modelId << " to "
                  << (device == DeviceType::CPU ? "CPU" : (device == DeviceType::GPU ? "GPU" : "NPU"))
                  << std::endl;

        std::unique_ptr<Backend> backend;
        switch (format) {
            case ModelFormat::ONNX: backend = std::make_unique<OnnxBackend>(); break;
            case ModelFormat::TFLITE:
            case ModelFormat::LITERT: backend = std::make_unique<TfLiteBackend>(); break;
            case ModelFormat::GGUF: backend = std::make_unique<GgufBackend>(); break;
            case ModelFormat::OPENVINO: backend = std::make_unique<OpenVinoBackend>(); break;
            case ModelFormat::PYTORCH: backend = std::make_unique<PyTorchBackend>(); break;
            default:
                std::cerr << "Unsupported format for " << modelId << std::endl;
                return false;
        }

        if (backend && backend->load(modelPath)) {
            m_backends[modelId] = std::move(backend);
            m_last_used[modelId] = std::chrono::steady_clock::now();
            return true;
        }
        return false;
    }

    std::string generate(const std::string& prompt, const std::string& modelId) {
        auto it = m_backends.find(modelId);
        if (it != m_backends.end()) {
            m_last_used[modelId] = std::chrono::steady_clock::now();
            return it->second->generate(prompt);
        }
        if (m_backends.size() == 1 && modelId.empty()) {
            m_last_used.begin()->second = std::chrono::steady_clock::now();
            return m_backends.begin()->second->generate(prompt);
        }
        return "Error: Model " + modelId + " not loaded.";
    }

    std::string runTask(const AiTask& task, const std::string& modelId) {
        auto it = m_backends.find(modelId);
        if (it != m_backends.end()) {
            m_last_used[modelId] = std::chrono::steady_clock::now();
            return it->second->runTask(task);
        }

        if (m_backends.size() == 1 && modelId.empty()) {
            m_last_used.begin()->second = std::chrono::steady_clock::now();
            return m_backends.begin()->second->runTask(task);
        }

        return "Error: Model " + modelId + " not loaded.";
    }

    bool unloadModel(const std::string& modelId) {
        MemoryOptimizer::handleDynamicUnloading(modelId);
        m_last_used.erase(modelId);
        return m_backends.erase(modelId) > 0;
    }

    void performMaintenance() {
        MemoryOptimizer::checkIdleModels(m_last_used);
    }

private:
    ModelFormat detectFormat(const std::string& path) {
        if (path.find(".gguf") != std::string::npos) return ModelFormat::GGUF;
        if (path.find(".onnx") != std::string::npos) return ModelFormat::ONNX;
        if (path.find(".tflite") != std::string::npos) return ModelFormat::TFLITE;
        if (path.find(".xml") != std::string::npos || path.find(".bin") != std::string::npos) return ModelFormat::OPENVINO;
        if (path.find(".pt") != std::string::npos || path.find(".pth") != std::string::npos) return ModelFormat::PYTORCH;
        return ModelFormat::AUTO;
    }

    std::unordered_map<std::string, std::unique_ptr<Backend>> m_backends;
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> m_last_used;
};

NanoRuntime::NanoRuntime() : pimpl(std::make_unique<Impl>()) {}
NanoRuntime::~NanoRuntime() = default;

bool NanoRuntime::loadModel(const std::string& modelPath, ModelFormat format) {
    return pimpl->loadModel(modelPath, "default", format);
}

bool NanoRuntime::loadModel(const std::string& modelPath, const std::string& modelId, ModelFormat format) {
    return pimpl->loadModel(modelPath, modelId, format);
}

std::string NanoRuntime::generate(const std::string& prompt) {
    return pimpl->generate(prompt, "");
}

std::string NanoRuntime::generate(const std::string& prompt, const std::string& modelId) {
    return pimpl->generate(prompt, modelId);
}

std::string NanoRuntime::runTask(const AiTask& task) {
    return pimpl->runTask(task, "");
}

std::string NanoRuntime::runTask(const AiTask& task, const std::string& modelId) {
    return pimpl->runTask(task, modelId);
}

bool NanoRuntime::convertModel(const std::string& inputPath,
                              const std::string& outputPath,
                              const ConversionConfig& config) {
    return ModelConverter::convert(inputPath, outputPath, config);
}

} // namespace nanoai

extern "C" {

nanoai_runtime_t nanoai_create() {
    return new nanoai::NanoRuntime();
}

void nanoai_destroy(nanoai_runtime_t handle) {
    delete static_cast<nanoai::NanoRuntime*>(handle);
}

bool nanoai_load_model(nanoai_runtime_t handle, const char* model_path) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    return runtime->loadModel(model_path);
}

bool nanoai_load_model_id(nanoai_runtime_t handle, const char* model_path, const char* model_id) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    return runtime->loadModel(model_path, model_id);
}

const char* nanoai_generate(nanoai_runtime_t handle, const char* prompt) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    static thread_local std::string result;
    result = runtime->generate(prompt);
    return result.c_str();
}

const char* nanoai_generate_id(nanoai_runtime_t handle, const char* prompt, const char* model_id) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    static thread_local std::string result;
    result = runtime->generate(prompt, model_id);
    return result.c_str();
}

const char* nanoai_run_ocr(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::VISION_OCR;
    task.visionInput = {std::vector<uint8_t>(buffer, buffer + (width * height * 3)), width, height, 3};
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_run_segmentation(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::VISION_SEGMENTATION;
    task.visionInput = {std::vector<uint8_t>(buffer, buffer + (width * height * 3)), width, height, 3};
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_detect_objects(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::VISION_OBJECT_DETECTION;
    task.visionInput = {std::vector<uint8_t>(buffer, buffer + (width * height * 3)), width, height, 3};
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_analyze_face(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::VISION_FACE_ANALYSIS;
    task.visionInput = {std::vector<uint8_t>(buffer, buffer + (width * height * 3)), width, height, 3};
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_analyze_document(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::VISION_DOCUMENT_ANALYSIS;
    task.visionInput = {std::vector<uint8_t>(buffer, buffer + (width * height * 3)), width, height, 3};
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_understand_report(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::VISION_REPORT_UNDERSTANDING;
    task.visionInput = {std::vector<uint8_t>(buffer, buffer + (width * height * 3)), width, height, 3};
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_recognize_speech(nanoai_runtime_t handle, const float* samples, int count) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::AUDIO_SPEECH_RECOGNITION;
    task.audioInput = {std::vector<float>(samples, samples + count), 16000};
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_detect_wake_word(nanoai_runtime_t handle, const float* samples, int count) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::AUDIO_WAKE_WORD;
    task.audioInput = {std::vector<float>(samples, samples + count), 16000};
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_summarize_text(nanoai_runtime_t handle, const char* text) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::TEXT_SUMMARIZATION;
    task.textInput = text;
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_translate_text(nanoai_runtime_t handle, const char* text) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::TEXT_TRANSLATION;
    task.textInput = text;
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

const char* nanoai_classify_text(nanoai_runtime_t handle, const char* text) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::TEXT_CLASSIFICATION;
    task.textInput = text;
    static thread_local std::string result;
    result = runtime->runTask(task);
    return result.c_str();
}

bool nanoai_convert_model(const char* input_path, const char* output_path, int quantization_type) {
    nanoai::ConversionConfig config;
    config.quantization = static_cast<nanoai::QuantizationType>(quantization_type);
    config.optimizeForNPU = true;
    config.enablePruning = false;
    return nanoai::NanoRuntime::convertModel(input_path, output_path, config);
}

bool nanoai_join_cluster(const char* cluster_id) {
    return nanoai::NetworkManager::initializeCluster(cluster_id);
}

bool nanoai_start_os_service() {
    return nanoai::AiOSService::startService();
}

} // extern "C"
