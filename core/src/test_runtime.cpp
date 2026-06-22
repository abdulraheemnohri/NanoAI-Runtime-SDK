#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    // 1. Test Model Conversion / Auto Quantization
    nanoai::ConversionConfig config;
    config.quantization = nanoai::QuantizationType::INT8;
    config.optimizeForNPU = true;

    bool converted = nanoai::NanoRuntime::convertModel("model.fp32", "model.int8", config);
    assert(converted);
    std::cout << "C++: Model conversion (INT8) successful." << std::endl;

    // 2. Test Multi-modal Tasks
    nanoai::NanoRuntime runtime;
    runtime.loadModel("vision_model.onnx");
    std::vector<uint8_t> dummy_image(100 * 100 * 3, 0);
    nanoai::AiTask vision_task;
    vision_task.type = nanoai::TaskType::VISION_OCR;
    vision_task.visionInput = {dummy_image, 100, 100, 3};
    std::string ocr_result = runtime.runTask(vision_task);
    std::cout << "OCR Result: " << ocr_result << std::endl;
    assert(ocr_result.find("[ONNX Backend]: OCR complete") != std::string::npos);

    std::cout << "C++ All Tests Passed!" << std::endl;
    return 0;
}
