#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    nanoai::NanoRuntime runtime;
    runtime.loadModel("full_suite.gguf");

    // 1. Test Translation
    std::string trans = nanoai_translate_text(reinterpret_cast<nanoai_runtime_t>(&runtime), "Hello world");
    std::cout << "Translation: " << trans << std::endl;
    assert(trans.find("Task processed") != std::string::npos);

    // 2. Test Classification
    std::string clazz = nanoai_classify_text(reinterpret_cast<nanoai_runtime_t>(&runtime), "NanoAI is fast");
    std::cout << "Classification: " << clazz << std::endl;
    assert(clazz.find("Task processed") != std::string::npos);

    // 3. Test Face Analysis
    uint8_t buffer[300]; // 10*10*3
    std::string face = nanoai_analyze_face(reinterpret_cast<nanoai_runtime_t>(&runtime), buffer, 10, 10);
    std::cout << "Face Analysis: " << face << std::endl;

    std::cout << "Core AI Task Set Expansion Tests Passed!" << std::endl;
    return 0;
}
