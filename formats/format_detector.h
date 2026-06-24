#ifndef NANOAI_FORMAT_DETECTOR_H
#define NANOAI_FORMAT_DETECTOR_H

#include <string>

namespace nanoai {
namespace formats {

enum class ModelFormat { UNKNOWN, GGUF, ONNX, TFLITE, COREML, OPENVINO };

class FormatDetector {
public:
    static ModelFormat detect(const std::string& path);
};

} }
#endif
