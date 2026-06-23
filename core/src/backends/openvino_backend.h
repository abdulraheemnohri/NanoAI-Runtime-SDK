#ifndef NANOAI_OPENVINO_BACKEND_H
#define NANOAI_OPENVINO_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class OpenVinoBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "OpenVINO Backend: Initializing with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[OpenVINO Backend]: Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        return "[OpenVINO Backend]: Task processed";
    }

    std::string getName() const override { return "OpenVINO"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_OPENVINO_BACKEND_H
