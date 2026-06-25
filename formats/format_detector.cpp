#include "format_detector.h"
#include <algorithm>

namespace nanoai {
namespace formats {

ModelFormat FormatDetector::detect(const std::string& path) {
    if (path.find(".gguf") != std::string::npos) return ModelFormat::GGUF;
    if (path.find(".onnx") != std::string::npos) return ModelFormat::ONNX;
    if (path.find(".tflite") != std::string::npos) return ModelFormat::TFLITE;
    if (path.find(".mlmodel") != std::string::npos) return ModelFormat::COREML;
    return ModelFormat::UNKNOWN;
}

} }
