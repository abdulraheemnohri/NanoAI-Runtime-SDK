#ifndef NANOAI_HEXAGON_BACKEND_H
#define NANOAI_HEXAGON_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class HexagonBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "Hexagon Backend: Initializing Qualcomm NPU with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[Hexagon Backend]: NPU Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        return "[Hexagon Backend]: NPU processed task for " + m_modelPath;
    }

    std::string getName() const override { return "Hexagon"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_HEXAGON_BACKEND_H
