#ifndef NANOAI_RUNTIME_H
#define NANOAI_RUNTIME_H

#include <string>
#include <memory>
#include "ai_task.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* nanoai_runtime_t;

nanoai_runtime_t nanoai_create();
void nanoai_destroy(nanoai_runtime_t handle);
bool nanoai_load_model(nanoai_runtime_t handle, const char* model_path);
const char* nanoai_generate(nanoai_runtime_t handle, const char* prompt);

// Task-based API for multi-modal
const char* nanoai_run_ocr(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height);
const char* nanoai_detect_wake_word(nanoai_runtime_t handle, const float* samples, int count);

#ifdef __cplusplus
} // extern "C"

namespace nanoai {

enum class ModelFormat {
    AUTO,
    ONNX,
    TFLITE,
    LITERT,
    GGUF,
    OPENVINO,
    PYTORCH
};

class NanoRuntime {
public:
    NanoRuntime();
    ~NanoRuntime();

    bool loadModel(const std::string& modelPath, ModelFormat format = ModelFormat::AUTO);
    std::string generate(const std::string& prompt);
    std::string runTask(const AiTask& task);

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};

} // namespace nanoai
#endif

#endif // NANOAI_RUNTIME_H
