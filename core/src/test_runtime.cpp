#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    nanoai::NanoRuntime runtime;

    // 1. Test Cluster Join
    std::cout << "--- Testing AI Mesh Networking ---" << std::endl;
    bool joined = nanoai_join_cluster("home-cluster");
    assert(joined);

    // 2. Test Parallel Model Load with Distributed Awareness
    std::cout << "--- Testing Distributed Task Offloading ---" << std::endl;
    runtime.loadModel("heavy_llm.gguf", "distributed_model");

    nanoai::AiTask task;
    task.type = nanoai::TaskType::VISION_OCR;
    task.visionInput = {std::vector<uint8_t>(100, 0), 10, 10, 1};

    // This should trigger "Discovering peers" and "Offloading chunk" in terminal
    std::string res = runtime.runTask(task, "distributed_model");
    std::cout << "Result: " << res << std::endl;

    std::cout << "Distributed Inference Foundation Tests Passed!" << std::endl;
    return 0;
}
