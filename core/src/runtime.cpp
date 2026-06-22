#include "nanoai/runtime.h"
#include "backend.h"
#include "backends/onnx_backend.h"
#include "backends/tflite_backend.h"
#include "backends/gguf_backend.h"
#include "acceleration/selector.h"
#include "memory/optimizer.h"
#include "conversion/converter.h"
#include <iostream>
#include <memory>

namespace nanoai {

class NanoRuntime::Impl {
public:
    Impl() : m_backend(nullptr) {}
    ~Impl() {}

    bool loadModel(const std::string& modelPath, ModelFormat format) {
        if (format == ModelFormat::AUTO) {
            format = detectFormat(modelPath);
        }

        MemoryOptimizer::applyOptimizations(modelPath);

        DeviceType device = SmartRuntimeSelector::selectBestDevice();
        std::cout << "Runtime: Automatically selected device: "
                  << (device == DeviceType::CPU ? "CPU" : (device == DeviceType::GPU ? "GPU" : "NPU"))
                  << std::endl;

        switch (format) {
            case ModelFormat::ONNX:
                m_backend = std::make_unique<OnnxBackend>();
                break;
            case ModelFormat::TFLITE:
            case ModelFormat::LITERT:
                m_backend = std::make_unique<TfLiteBackend>();
                break;
            case ModelFormat::GGUF:
                m_backend = std::make_unique<GgufBackend>();
                break;
            default:
                std::cerr << "Unsupported or unknown model format for path: " << modelPath << std::endl;
                return false;
        }

        if (m_backend) {
            return m_backend->load(modelPath);
        }
        return false;
    }

    std::string generate(const std::string& prompt) {
        if (m_backend) {
            return m_backend->generate(prompt);
        }
        return "Error: No model loaded.";
    }

    std::string runTask(const AiTask& task) {
        if (m_backend) {
            return m_backend->runTask(task);
        }
        return "Error: No model loaded.";
    }

private:
    ModelFormat detectFormat(const std::string& path) {
        if (path.find(".gguf") != std::string::npos) return ModelFormat::GGUF;
        if (path.find(".onnx") != std::string::npos) return ModelFormat::ONNX;
        if (path.find(".tflite") != std::string::npos) return ModelFormat::TFLITE;
        return ModelFormat::AUTO;
    }

    std::unique_ptr<Backend> m_backend;
};

NanoRuntime::NanoRuntime() : pimpl(std::make_unique<Impl>()) {}
NanoRuntime::~NanoRuntime() = default;

bool NanoRuntime::loadModel(const std::string& modelPath, ModelFormat format) {
    return pimpl->loadModel(modelPath, format);
}

std::string NanoRuntime::generate(const std::string& prompt) {
    return pimpl->generate(prompt);
}

std::string NanoRuntime::runTask(const AiTask& task) {
    return pimpl->runTask(task);
}

bool NanoRuntime::convertModel(const std::string& inputPath,
                              const std::string& outputPath,
                              const ConversionConfig& config) {
    return ModelConverter::convert(inputPath, outputPath, config);
}

} // namespace nanoai

// C API Implementation
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

const char* nanoai_generate(nanoai_runtime_t handle, const char* prompt) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    static thread_local std::string result;
    result = runtime->generate(prompt);
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

const char* nanoai_detect_wake_word(nanoai_runtime_t handle, const float* samples, int count) {
    auto* runtime = static_cast<nanoai::NanoRuntime*>(handle);
    nanoai::AiTask task;
    task.type = nanoai::TaskType::AUDIO_WAKE_WORD;
    task.audioInput = {std::vector<float>(samples, samples + count), 16000};
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

} // extern "C"
