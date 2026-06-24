#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    nanoai::NanoRuntime runtime;

    struct TestCase {
        std::string model_path;
        std::string model_id;
        std::string expected_backend_init_log;
    };

    std::vector<TestCase> cases = {
        {"chat.gguf", "chat", "GGUF Backend: Initializing"},
        {"ocr.onnx", "ocr", "Onnx Backend: Initializing"},
        {"segment.tflite", "segment", "TFLite Backend: Initializing"},
        {"detect.xml", "detect", "OpenVino Backend: Initializing"},
        {"classify.pt", "classify", "PyTorch Backend: Initializing"}
    };

    for (const auto& tc : cases) {
        std::cout << "--- Testing Model: " << tc.model_id << " (" << tc.model_path << ") ---" << std::endl;
        bool loaded = runtime.loadModel(tc.model_path, tc.model_id);
        assert(loaded);

        std::string hw = runtime.getDetectedHardware(tc.model_id);
        std::cout << "  Routed to: " << hw << std::endl;
        assert(!hw.empty() && hw != "Unknown");

        std::string res = runtime.generate("test prompt", tc.model_id);
        std::cout << "  Response: " << res << std::endl;
        assert(res.find("Response to") != std::string::npos);
    }

    std::cout << "Comprehensive routing verification passed!" << std::endl;
    return 0;
}
