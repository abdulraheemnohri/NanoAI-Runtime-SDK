#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>

int main() {
    nanoai::NanoRuntime runtime;

    // Test default model hardware info
    runtime.loadModel("test.gguf");
    std::string hw = runtime.getDetectedHardware("default");
    std::cout << "Detected hardware for default model: " << hw << std::endl;
    assert(!hw.empty());
    assert(hw != "Unknown");

    // Test specific model ID hardware info
    runtime.loadModel("test.tflite", "vision_model");
    std::string hw_vision = runtime.getDetectedHardware("vision_model");
    std::cout << "Detected hardware for vision_model: " << hw_vision << std::endl;
    assert(!hw_vision.empty());
    assert(hw_vision != "Unknown");

    std::cout << "Hardware exposure test passed!" << std::endl;
    return 0;
}
