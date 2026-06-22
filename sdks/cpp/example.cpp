#include "nanoai/runtime.h"
#include <iostream>

int main() {
    nanoai::NanoRuntime runtime;

    if (runtime.loadModel("gemma.gguf")) {
        std::cout << "C++ SDK: Model loaded" << std::endl;
    }

    std::string response = runtime.generate("Hello from C++ SDK");
    std::cout << "Response: " << response << std::endl;

    return 0;
}
