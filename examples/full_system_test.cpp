#include "nanoai/runtime.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main() {
    std::cout << "=== NanoAI v2 Full System Integration Test ===" << std::endl;

    nanoai::NanoRuntime rt;

    // 1. Hardware & Telemetry
    std::cout << "\n[1/5] Checking Hardware & Telemetry..." << std::endl;
    std::cout << "Hardware Profile: " << rt.getHardwareProfile() << std::endl;
    std::cout << "Initial Telemetry: " << rt.getRuntimeTelemetry() << std::endl;

    // 2. Model Management
    std::cout << "\n[2/5] Testing Model Loading..." << std::endl;
    rt.loadModel("models/llama3.gguf", "chat_model");
    rt.loadModel("models/yolo.tflite", "vision_model");

    // 3. Swarm Intelligence
    std::cout << "\n[3/5] Testing Swarm Intelligence..." << std::endl;
    std::vector<std::string> agents = {"CodingAgent", "ResearchAgent"};
    std::string swarmRes = rt.runSwarm("feature_impl", agents, "Implement a prime checker in Python");
    std::cout << "Swarm Result: " << swarmRes << std::endl;

    // 4. Workflow Engine
    std::cout << "\n[4/5] Testing Workflow Engine..." << std::endl;
    std::string workflowJson = R"({"pipeline": ["ocr", "translate"]})";
    std::string flowRes = rt.runWorkflow(workflowJson, "image_data_001");
    std::cout << "Workflow Result: " << flowRes << std::endl;

    // 5. AI OS Layer
    std::cout << "\n[5/5] Testing AI OS Layer..." << std::endl;
    if (rt.bootOS()) {
        std::string dispatchRes = rt.osDispatch("optimize_all_resources");
        std::cout << "OS Dispatch Result: " << dispatchRes << std::endl;
    }

    // Cluster discovery simulation
    std::cout << "\nWaiting for cluster node discovery..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Cluster Nodes: " << rt.getClusterNodes() << std::endl;

    std::cout << "\n=== Full System Test Complete ===" << std::endl;
    return 0;
}
