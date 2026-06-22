#ifndef NANOAI_RUNTIME_H
#define NANOAI_RUNTIME_H

#include <string>
#include <memory>

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

    /**
     * Load a model from the specified path.
     * @param modelPath Path to the model file.
     * @param format Model format. If AUTO, the runtime will attempt to detect the format.
     * @return true if the model was loaded successfully, false otherwise.
     */
    bool loadModel(const std::string& modelPath, ModelFormat format = ModelFormat::AUTO);

    /**
     * Generate a response based on the input prompt.
     * @param prompt The input text prompt.
     * @return The generated response string.
     */
    std::string generate(const std::string& prompt);

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};

} // namespace nanoai

#endif // NANOAI_RUNTIME_H
