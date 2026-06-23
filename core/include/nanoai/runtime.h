#ifndef NANOAI_RUNTIME_H
#define NANOAI_RUNTIME_H

#include <string>
#include <memory>
#include "ai_task.h"
#include "model_conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* nanoai_runtime_t;

nanoai_runtime_t nanoai_create();
void nanoai_destroy(nanoai_runtime_t handle);
bool nanoai_load_model(nanoai_runtime_t handle, const char* model_path);
bool nanoai_load_model_id(nanoai_runtime_t handle, const char* model_path, const char* model_id);
const char* nanoai_generate(nanoai_runtime_t handle, const char* prompt);
const char* nanoai_generate_id(nanoai_runtime_t handle, const char* prompt, const char* model_id);

// Task-based API for multi-modal
const char* nanoai_run_ocr(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height);
const char* nanoai_run_segmentation(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height);
const char* nanoai_detect_objects(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height);
const char* nanoai_analyze_face(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height);
const char* nanoai_analyze_document(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height);
const char* nanoai_understand_report(nanoai_runtime_t handle, const uint8_t* buffer, int width, int height);
const char* nanoai_recognize_speech(nanoai_runtime_t handle, const float* samples, int count);
const char* nanoai_detect_wake_word(nanoai_runtime_t handle, const float* samples, int count);
const char* nanoai_summarize_text(nanoai_runtime_t handle, const char* text);
const char* nanoai_translate_text(nanoai_runtime_t handle, const char* text);
const char* nanoai_classify_text(nanoai_runtime_t handle, const char* text);

// Model Conversion API
bool nanoai_convert_model(const char* input_path, const char* output_path, int quantization_type);

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
    bool loadModel(const std::string& modelPath, const std::string& modelId, ModelFormat format = ModelFormat::AUTO);

    std::string generate(const std::string& prompt);
    std::string generate(const std::string& prompt, const std::string& modelId);

    std::string runTask(const AiTask& task);
    std::string runTask(const AiTask& task, const std::string& modelId);

    static bool convertModel(const std::string& inputPath,
                            const std::string& outputPath,
                            const ConversionConfig& config);

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};

} // namespace nanoai
#endif

#endif // NANOAI_RUNTIME_H
