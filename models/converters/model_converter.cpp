#include "model_converter.h"
#include <iostream>

namespace nanoai {
namespace models {

bool ModelConverter::convertToGGUF(const std::string& in, const std::string& out) {
    std::cout << "Converter: Transforming " << in << " to GGUF format..." << std::endl;
    return true;
}

bool ModelConverter::convertToONNX(const std::string& in, const std::string& out) {
    std::cout << "Converter: Exporting " << in << " to ONNX graph..." << std::endl;
    return true;
}

} }
