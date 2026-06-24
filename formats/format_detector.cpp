#include "format_detector.h"
#include <algorithm>

namespace nanoai {
namespace formats {

ModelFormat FormatDetector::detect(const std::string& path) {
    if (path.find(".gguf") != std::string::npos) return ModelFormat::GGUF;
    if (path.find(".onnx") != std::string::npos) return ModelFormat::ONNX;
    if (path.find(".tflite") != std::string::npos) return ModelFormat::TFLITE;
    if (path.find(".mlmodel") != std::string::npos) return ModelFormat::COREML;
    if (path.find(".xml") != std::string::npos || path.find(".bin") != std::string::npos) return ModelFormat::OPENVINO;
    if (path.find(".safetensors") != std::string::npos) return ModelFormat::SAFETENSORS;
    return ModelFormat::UNKNOWN;
}

std::string FormatDetector::formatToString(ModelFormat format) {
    switch(format) {
        case ModelFormat::GGUF: return "GGUF";
        case ModelFormat::ONNX: return "ONNX";
        case ModelFormat::TFLITE: return "TFLITE";
        case ModelFormat::COREML: return "COREML";
        case ModelFormat::OPENVINO: return "OPENVINO";
        case ModelFormat::SAFETENSORS: return "SAFETENSORS";
        default: return "UNKNOWN";
    }
}

} // namespace formats
} // namespace nanoai
