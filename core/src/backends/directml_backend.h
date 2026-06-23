#ifndef NANOAI_DIRECTML_BACKEND_H
#define NANOAI_DIRECTML_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class DirectMLBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "DirectML Backend: Initializing with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[DirectML Backend]: Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        return "[DirectML Backend]: Task processed";
    }

    std::string getName() const override { return "DirectML"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_DIRECTML_BACKEND_H
