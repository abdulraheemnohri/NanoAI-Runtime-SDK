#ifndef NANOAI_APU_BACKEND_H
#define NANOAI_APU_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class ApuBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "APU Backend: Initializing MediaTek NPU with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[APU Backend]: NPU Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        return "[APU Backend]: NPU processed task for " + m_modelPath;
    }

    std::string getName() const override { return "APU"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_APU_BACKEND_H
