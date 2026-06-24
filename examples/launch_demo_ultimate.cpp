#include "nanoai/runtime.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main() {
    std::cout << "🌌 NANOAI RUNTIME X — THE ULTIMATE AI ORCHESTRATION LAYER 🌌" << std::endl;

    nanoai::NanoRuntime nrx;

    std::cout << "\n[1] HARDWARE AUTO-DISCOVERY..." << std::endl;
    std::cout << nrx.getHardwareProfile() << std::endl;

    std::cout << "\n[2] DEPLOYING MULTI-MODAL PARALLEL PIPELINE..." << std::endl;
    // Map models to specific hardware targets
    nrx.loadModel("gemma-2b.gguf", "core_llm");      // Target: NPU
    nrx.loadModel("whisper-v3.onnx", "voice_stt");    // Target: GPU
    nrx.loadModel("yolov8.tflite", "vision_det");     // Target: GPU
    nrx.loadModel("bge-small.gguf", "embeddings");    // Target: CPU
    nrx.loadModel("ocr-v2.bin", "ocr_engine");        // Target: DSP

    std::cout << "\n[3] INITIATING SWARM COLLABORATION..." << std::endl;
    std::vector<std::string> swarm = {"ResearchAgent", "CodingAgent", "VisionAgent", "SpeechAgent"};
    std::string swarmRes = nrx.runSwarm("AUTONOMOUS_RESEARCH", swarm, "Analyze current hardware telemetry and optimize load.");
    std::cout << "Swarm: " << swarmRes << std::endl;

    std::cout << "\n[4] EXECUTING VISUAL WORKFLOW..." << std::endl;
    std::string flow = R"({"pipeline": ["ocr", "translate", "summarize"]})";
    std::string flowRes = nrx.runWorkflow(flow, "multi_modal_stream_0xAF3");
    std::cout << "Workflow: " << flowRes << std::endl;

    std::cout << "\n[5] BOOTING AI OS KERNEL..." << std::endl;
    if (nrx.bootOS()) {
        std::cout << "OS Layer: " << nrx.osDispatch("GLOBAL_LOAD_REBALANCE") << std::endl;
    }

    std::cout << "\n[6] REAL-TIME PERFORMANCE METRICS..." << std::endl;
    std::cout << nrx.getRuntimeTelemetry() << std::endl;

    std::cout << "\n🌟 NRX: THE FUTURE OF ON-DEVICE INTELLIGENCE IS HERE. 🌟" << std::endl;

    return 0;
}
