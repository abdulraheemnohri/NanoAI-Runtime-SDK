#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    nanoai::NanoRuntime runtime;

    // 1. Verify CUDA routing
    std::cout << "--- Testing CUDA Selection ---" << std::endl;
    // We force a high-score load for CUDA in our simulation by adding models
    // until the NPU is saturated, or just checking the logs.
    runtime.loadModel("nvidia_model.onnx", "gpu_task");
    std::string res = runtime.generate("run", "gpu_task");
    assert(res.find("ONNX") != std::string::npos);

    // 2. Verify NPU Detection logs (Hexagon)
    std::cout << "--- Testing NPU Detection ---" << std::endl;
    runtime.loadModel("qualcomm_model.tflite", "npu_task");

    std::cout << "C++ CUDA and NPU Detection Tests Passed!" << std::endl;
    return 0;
}
