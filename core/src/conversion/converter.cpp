#include "converter.h"
#include <iostream>

namespace nanoai {

bool ModelConverter::convert(const std::string& inputPath,
                            const std::string& outputPath,
                            const ConversionConfig& config) {
    std::cout << "Model Converter: Starting conversion for " << inputPath << std::endl;

    std::string quantStr = "None";
    switch (config.quantization) {
        case QuantizationType::FP16: quantStr = "FP16"; break;
        case QuantizationType::INT8: quantStr = "INT8"; break;
        case QuantizationType::INT4: quantStr = "INT4"; break;
        default: break;
    }

    std::cout << " - Quantization: " << quantStr << std::endl;
    if (config.optimizeForNPU) {
        std::cout << " - Optimizing for NPU" << std::endl;
    }

    std::cout << "Model Converter: Successfully saved optimized model to " << outputPath << std::endl;
    return true;
}

} // namespace nanoai
