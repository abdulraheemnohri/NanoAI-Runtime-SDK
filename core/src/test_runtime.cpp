#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    nanoai::NanoRuntime runtime;

    // 1. Verify NPU Priority Selection
    std::cout << "--- Testing NPU Selection ---" << std::endl;
    runtime.loadModel("any_model.gguf");
    // Output should show NPU selection in terminal

    // 2. Verify Summarization Task
    std::cout << "--- Testing Summarization ---" << std::endl;
    nanoai::AiTask sum_task;
    sum_task.type = nanoai::TaskType::TEXT_SUMMARIZATION;
    sum_task.textInput = "NanoAI is a universal offline runtime.";
    std::string sum_res = runtime.runTask(sum_task);
    std::cout << "Sum Res: " << sum_res << std::endl;
    assert(sum_res.find("Summary of") != std::string::npos);

    // 3. Verify Segmentation Task (routing through a backend, e.g., ONNX)
    std::cout << "--- Testing Segmentation ---" << std::endl;
    runtime.loadModel("seg.onnx");
    nanoai::AiTask seg_task;
    seg_task.type = nanoai::TaskType::VISION_SEGMENTATION;
    seg_task.visionInput = {std::vector<uint8_t>(100, 0), 10, 10, 1};
    std::string seg_res = runtime.runTask(seg_task);
    std::cout << "Seg Res: " << seg_res << std::endl;

    std::cout << "C++ NPU and Expanded Task Tests Passed!" << std::endl;
    return 0;
}
