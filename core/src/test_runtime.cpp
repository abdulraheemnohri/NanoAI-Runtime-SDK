#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>

int main() {
    nanoai::NanoRuntime runtime;

    // Test GGUF format
    bool loaded = runtime.loadModel("test.gguf");
    assert(loaded);
    std::string result = runtime.generate("Hello");
    std::cout << "GGUF Result: " << result << std::endl;
    assert(result.find("[GGUF Backend]") != std::string::npos);

    // Test ONNX format
    loaded = runtime.loadModel("test.onnx");
    assert(loaded);
    result = runtime.generate("Hello");
    std::cout << "ONNX Result: " << result << std::endl;
    assert(result.find("[ONNX Backend]") != std::string::npos);

    // Test TFLite format
    loaded = runtime.loadModel("test.tflite");
    assert(loaded);
    result = runtime.generate("Hello");
    std::cout << "TFLite Result: " << result << std::endl;
    assert(result.find("[TFLite Backend]") != std::string::npos);

    std::cout << "Backend Routing Test Passed!" << std::endl;
    return 0;
}
