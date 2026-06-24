#include "nanoai/runtime.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    nanoai::NanoRuntime runtime;
    std::cout << "--- NanoAI v2.1 Distributed & Dynamic Scheduling Test ---" << std::endl;

    // 1. Loading Models
    runtime.loadModel("llama-3-8b.gguf", "chat_model");
    runtime.loadModel("yolov8.onnx", "vision_model");

    // 2. High throughput burst to trigger scheduling/offloading
    std::cout << "\n[Execution] Sending high-throughput burst..." << std::endl;
    for(int i=0; i<8; ++i) {
        runtime.generate("Hello " + std::to_string(i), "chat_model", (i % 2 == 0) ? nanoai::TaskPriority::CRITICAL : nanoai::TaskPriority::NORMAL);
    }

    // 3. Wait for discovery to happen in background
    std::cout << "\n[Discovery] Waiting for remote node discovery..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(7));

    // 4. Send more tasks (these should potentially offload)
    std::cout << "\n[Execution] Sending more tasks for offloading test..." << std::endl;
    runtime.generate("Analyze this frame", "vision_model", nanoai::TaskPriority::BACKGROUND);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "\n[Final State] System Report:" << std::endl;
    std::cout << runtime.getClusterNodes() << std::endl;
    std::cout << runtime.getRuntimeTelemetry() << std::endl;

    return 0;
}
