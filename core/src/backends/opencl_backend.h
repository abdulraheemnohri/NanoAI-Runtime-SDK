#ifndef NANOAI_OPENCL_BACKEND_H
#define NANOAI_OPENCL_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class OpenCLBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "OpenCL Backend: Initializing with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[OpenCL Backend]: Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        return "[OpenCL Backend]: Task processed";
    }

    std::string getName() const override { return "OpenCL"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_OPENCL_BACKEND_H
