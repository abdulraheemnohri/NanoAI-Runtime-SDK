#ifndef NANOAI_VULKAN_BACKEND_H
#define NANOAI_VULKAN_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class VulkanBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "Vulkan Backend: Initializing on GPU with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[Vulkan Backend]: GPU Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        return "[Vulkan Backend]: GPU processed task for " + m_modelPath;
    }

    std::string getName() const override { return "Vulkan"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_VULKAN_BACKEND_H
