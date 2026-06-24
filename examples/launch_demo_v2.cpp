#include "nanoai/runtime.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main() {
    nanoai::NanoRuntime runtime;
    std::cout << "🚀 NANOAI RUNTIME v2.0 — ULTIMATE LAUNCH DEMO 🚀" << std::endl;

    // 1. HARDWARE ORCHESTRATION (HAL)
    std::cout << "\n[1] AUTO-DETECTING HARDWARE CAPABILITIES..." << std::endl;
    std::cout << runtime.getHardwareProfile() << std::endl;

    // 2. PARALLEL MULTI-MODEL LOADING
    std::cout << "\n[2] LOADING NEURAL ENGINE ASSETS..." << std::endl;
    runtime.loadModel("gemma-7b-q4.gguf", "primary_llm");
    runtime.loadModel("whisper-v3.onnx", "audio_stt");
    runtime.loadModel("yolov8x.tflite", "vision_det");

    // 3. DISTRIBUTED CLUSTER DISCOVERY
    std::cout << "\n[3] SCANNING LOCAL NETWORK FOR AI CLUSTER NODES..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Nodes Found: " << runtime.getClusterNodes() << std::endl;

    // 4. SWARM INTELLIGENCE & AGENT COLLABORATION
    std::cout << "\n[4] EXECUTING AI SWARM (Collaborative Agents)..." << std::endl;
    std::vector<std::string> agentChain = {"ResearchAgent", "CodingAgent"};
    std::string swarmResult = runtime.runSwarm("Project_Alpha", agentChain, "Design a sustainable energy system");
    std::cout << "Swarm Output: " << swarmResult << std::endl;

    // 5. HIGH-THROUGHPUT SCHEDULING
    std::cout << "\n[5] STRESS TESTING PARALLEL SCHEDULER..." << std::endl;
    for(int i=0; i<5; ++i) {
        runtime.generate("Background task " + std::to_string(i), "primary_llm", nanoai::TaskPriority::BACKGROUND);
    }
    std::cout << runtime.generate("USER INTERRUPT: STOP ALL", "primary_llm", nanoai::TaskPriority::CRITICAL) << std::endl;

    // 6. PIPELINE WORKFLOWS
    std::cout << "\n[6] RUNNING VISION -> OCR -> TRANSLATION PIPELINE..." << std::endl;
    std::cout << runtime.runWorkflow("{}", "camera_input_frame_001.raw") << std::endl;

    // 7. TELEMETRY MONITORING
    std::cout << "\n[7] REAL-TIME TELEMETRY FEED (NPU/GPU/CPU)..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << runtime.getRuntimeTelemetry() << std::endl;

    std::cout << "\n✅ NANOAI RUNTIME IS READY FOR PRODUCTION DEPLOYMENT." << std::endl;
    return 0;
}
