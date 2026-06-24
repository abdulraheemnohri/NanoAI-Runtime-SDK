#include "nanoai/runtime.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    nanoai::NanoRuntime runtime;
    std::cout << "--- NanoAI v2 Universal HAL & Parallel Runtime Test ---" << std::endl;

    std::cout << "\n[1] Hardware Profile (Auto-Discovery):" << std::endl;
    std::cout << runtime.getHardwareProfile() << std::endl;

    std::cout << "\n[2] Parallel Task Execution (Multi-Model):" << std::endl;
    runtime.loadModel("gemma-2b.gguf", "chat_model");
    runtime.loadModel("whisper.onnx", "voice_model");

    std::cout << runtime.generate("Hello", "chat_model", nanoai::TaskPriority::CRITICAL) << std::endl;
    std::cout << runtime.generate("Transcribe this", "voice_model", nanoai::TaskPriority::NORMAL) << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\n[3] Telemetry:" << std::endl;
    std::cout << runtime.getRuntimeTelemetry() << std::endl;

    return 0;
}
