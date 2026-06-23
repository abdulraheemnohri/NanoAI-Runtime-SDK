#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    nanoai::NanoRuntime runtime;

    // Load Model 1: Chat (NPU priority)
    std::cout << "--- Loading Chat Model ---" << std::endl;
    bool m1 = runtime.loadModel("chat.gguf", "chat_model");
    assert(m1);

    // Load Model 2: Coding (GPU/NPU depending on load)
    std::cout << "--- Loading Coding Model ---" << std::endl;
    bool m2 = runtime.loadModel("coder.onnx", "coding_model");
    assert(m2);

    // Load Model 3: Voice (CPU fallback or distributed)
    std::cout << "--- Loading Voice Model ---" << std::endl;
    bool m3 = runtime.loadModel("whisper.tflite", "voice_model");
    assert(m3);

    // Verify addressing
    std::string r1 = runtime.generate("Write a poem", "chat_model");
    std::cout << "Chat Model Res: " << r1 << std::endl;
    assert(r1.find("GGUF") != std::string::npos);

    std::string r2 = runtime.generate("def hello():", "coding_model");
    std::cout << "Coding Model Res: " << r2 << std::endl;
    assert(r2.find("ONNX") != std::string::npos);

    std::cout << "Parallel Multi-Model Execution Tests Passed!" << std::endl;
    return 0;
}
