#ifndef NANOAI_CUDA_BACKEND_H
#define NANOAI_CUDA_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class CudaBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "CUDA Backend: Initializing NVIDIA GPU with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[CUDA Backend]: GPU Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        return "[CUDA Backend]: GPU processed task for " + m_modelPath;
    }

    std::string getName() const override { return "CUDA"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_CUDA_BACKEND_H
