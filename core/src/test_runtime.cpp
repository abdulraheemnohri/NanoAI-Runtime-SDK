#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    nanoai::NanoRuntime runtime;

    // 1. Test OpenVINO routing
    assert(runtime.loadModel("model.xml"));
    std::string ov_res = runtime.generate("test");
    std::cout << "OpenVINO Result: " << ov_res << std::endl;
    assert(ov_res.find("OpenVINO") != std::string::npos);

    // 2. Test PyTorch routing
    assert(runtime.loadModel("model.pt"));
    std::string pt_res = runtime.generate("test");
    std::cout << "PyTorch Result: " << pt_res << std::endl;
    assert(pt_res.find("PyTorch") != std::string::npos);

    // 3. Test multi-task routing
    nanoai::AiTask task;
    task.type = nanoai::TaskType::VISION_OCR;
    task.visionInput = {std::vector<uint8_t>(10, 0), 10, 1, 1};
    std::string ocr_res = runtime.runTask(task);
    std::cout << "OCR Result: " << ocr_res << std::endl;

    std::cout << "Backend Expansion Tests Passed!" << std::endl;
    return 0;
}
