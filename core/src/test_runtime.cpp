#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>

int main() {
    nanoai::NanoRuntime runtime;

    // Test format detection
    bool loaded = runtime.loadModel("test.gguf");
    assert(loaded);

    // Test generation
    std::string result = runtime.generate("Hello");
    std::cout << "Result: " << result << std::endl;
    assert(result.find("Responding to \"Hello\"") != std::string::npos);

    std::cout << "C++ API Test Passed!" << std::endl;
    return 0;
}
