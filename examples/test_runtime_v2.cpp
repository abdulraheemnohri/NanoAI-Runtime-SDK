#include "nanoai/runtime.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    nanoai::NanoRuntime runtime;
    std::cout << "--- NanoAI v2 Universal Hardware Compatibility Test ---" << std::endl;

    std::cout << "\n[HAL Discovery] Global Capability Profile:" << std::endl;
    std::cout << runtime.getHardwareProfile() << std::endl;

    std::cout << "\n[Scheduling] Distributing tasks across disparate hardware..." << std::endl;

    runtime.loadModel("gemma.gguf", "chat_npu");
    runtime.loadModel("whisper.onnx", "audio_gpu");
    runtime.loadModel("yolo.tflite", "vision_gpu");
    runtime.loadModel("phi.gguf", "research_cpu");

    std::cout << runtime.generate("agent:CodingAgent write a HAL plugin", "chat_npu", nanoai::TaskPriority::CRITICAL) << std::endl;
    std::cout << runtime.generate("Transcribe the user's voice", "audio_gpu", nanoai::TaskPriority::HIGH) << std::endl;
    std::cout << runtime.generate("Detect security threats", "vision_gpu", nanoai::TaskPriority::NORMAL) << std::endl;
    std::cout << runtime.generate("Summarize the logs", "research_cpu", nanoai::TaskPriority::BACKGROUND) << std::endl;

    std::cout << "\n[Distributed] Scanning for cluster nodes..." << std::endl;
    std::cout << runtime.getClusterNodes() << std::endl;

    std::cout << "\n[Telemetry] Current System State:" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << runtime.getRuntimeTelemetry() << std::endl;

    return 0;
}
