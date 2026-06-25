#ifndef NANOAI_FORMAT_DETECTOR_H
#define NANOAI_FORMAT_DETECTOR_H

#include <string>

namespace nanoai {
namespace formats {

enum class ModelFormat { UNKNOWN, GGUF, ONNX, TFLITE, COREML, OPENVINO, SAFETENSORS };

class FormatDetector {
public:
    static ModelFormat detect(const std::string& path);
    static std::string formatToString(ModelFormat format);
};

} // namespace formats
} // namespace nanoai

#endif // NANOAI_FORMAT_DETECTOR_H
