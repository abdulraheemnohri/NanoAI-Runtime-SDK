#ifndef NANOAI_METAL_BACKEND_H
#define NANOAI_METAL_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class MetalBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "Metal Backend: Initializing with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[Metal Backend]: Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        return "[Metal Backend]: Task processed";
    }

    std::string getName() const override { return "Metal"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_METAL_BACKEND_H
