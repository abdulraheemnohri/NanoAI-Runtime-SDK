#ifndef NANOAI_ONNX_BACKEND_H
#define NANOAI_ONNX_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class OnnxBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "ONNX Backend: Initializing with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[ONNX Backend]: Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string getName() const override { return "ONNX"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_ONNX_BACKEND_H
