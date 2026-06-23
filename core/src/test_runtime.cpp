#include "nanoai/runtime.h"
#include "../src/acceleration/cpu_info.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    // 1. Test CPU Architecture Detection
    std::cout << "C++: Detected Architecture: " << nanoai::CpuInfo::getArchitectureName() << std::endl;

    // 2. Test Model Conversion
    nanoai::ConversionConfig config;
    config.quantization = nanoai::QuantizationType::INT4;
    config.optimizeForNPU = true;
    bool converted = nanoai::NanoRuntime::convertModel("llama.fp32", "llama.int4", config);
    assert(converted);

    // 3. Test New AI Tasks
    nanoai::NanoRuntime runtime;
    runtime.loadModel("multimodal.onnx");

    // OCR
    nanoai::AiTask ocr_task;
    ocr_task.type = nanoai::TaskType::VISION_OCR;
    ocr_task.visionInput = {std::vector<uint8_t>(10, 0), 10, 1, 1};
    std::string ocr_res = runtime.runTask(ocr_task);
    std::cout << "C++ OCR: " << ocr_res << std::endl;
    assert(ocr_res.find("OCR complete") != std::string::npos);

    // Object Detection
    nanoai::AiTask det_task;
    det_task.type = nanoai::TaskType::VISION_OBJECT_DETECTION;
    det_task.visionInput = {std::vector<uint8_t>(10, 0), 10, 1, 1};
    std::string det_res = runtime.runTask(det_task);
    std::cout << "C++ Detection: " << det_res << std::endl;

    std::cout << "C++ AI Task Expansion Tests Passed!" << std::endl;
    return 0;
}
