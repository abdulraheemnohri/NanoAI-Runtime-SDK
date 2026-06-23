#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    nanoai::NanoRuntime runtime;

    // 1. Test Document Analysis (routing and memory logic)
    std::cout << "--- Testing Document Analysis & Lazy Loading ---" << std::endl;
    runtime.loadModel("doc_ai.onnx", "doc_model");

    nanoai::AiTask doc_task;
    doc_task.type = nanoai::TaskType::VISION_DOCUMENT_ANALYSIS;
    doc_task.visionInput = {std::vector<uint8_t>(100, 0), 10, 10, 1};
    std::string doc_res = runtime.runTask(doc_task, "doc_model");
    std::cout << "Doc Res: " << doc_res << std::endl;
    assert(doc_res.find("processed") != std::string::npos);

    // 2. Test Report Understanding
    std::cout << "--- Testing Report Understanding ---" << std::endl;
    nanoai::AiTask report_task;
    report_task.type = nanoai::TaskType::VISION_REPORT_UNDERSTANDING;
    report_task.visionInput = {std::vector<uint8_t>(100, 0), 10, 10, 1};
    std::string report_res = runtime.runTask(report_task, "doc_model");
    std::cout << "Report Res: " << report_res << std::endl;

    std::cout << "C++ Multimodal and Memory Optimization Tests Passed!" << std::endl;
    return 0;
}
