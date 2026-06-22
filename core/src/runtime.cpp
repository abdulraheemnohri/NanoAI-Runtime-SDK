#include "nanoai/runtime.h"
#include <iostream>
#include <vector>

namespace nanoai {

class NanoRuntime::Impl {
public:
    Impl() {}
    ~Impl() {}

    bool loadModel(const std::string& modelPath, ModelFormat format) {
        std::cout << "Loading model from: " << modelPath << std::endl;

        if (format == ModelFormat::AUTO) {
            format = detectFormat(modelPath);
        }

        m_format = format;
        m_modelPath = modelPath;
        return true;
    }

    std::string generate(const std::string& prompt) {
        return "NanoAI [Offline Mode]: Responding to \"" + prompt + "\" using model " + m_modelPath;
    }

    // Keep the last result for C API string persistence
    std::string last_result;

private:
    ModelFormat detectFormat(const std::string& path) {
        if (path.find(".gguf") != std::string::npos) return ModelFormat::GGUF;
        if (path.find(".onnx") != std::string::npos) return ModelFormat::ONNX;
        if (path.find(".tflite") != std::string::npos) return ModelFormat::TFLITE;
        return ModelFormat::AUTO;
    }

    ModelFormat m_format;
    std::string m_modelPath;
};

NanoRuntime::NanoRuntime() : pimpl(std::make_unique<Impl>()) {}
NanoRuntime::~NanoRuntime() = default;

bool NanoRuntime::loadModel(const std::string& modelPath, ModelFormat format) {
    return pimpl->loadModel(modelPath, format);
}

std::string NanoRuntime::generate(const std::string& prompt) {
    return pimpl->generate(prompt);
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
    // This is a bit unsafe as the string is temporary,
    // but for our skeleton it's fine if we return a persistent pointer or manage memory.
    // Let's use a static thread-local buffer or modify Impl to hold the last result.
    // For now, let's keep it simple and just return a leaked or managed string.
    static thread_local std::string result;
    result = runtime->generate(prompt);
    return result.c_str();
}

} // extern "C"
