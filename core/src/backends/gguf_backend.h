#ifndef NANOAI_GGUF_BACKEND_H
#define NANOAI_GGUF_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class GgufBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "GGUF Backend: Initializing with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[GGUF Backend]: Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        if (task.type == TaskType::TEXT_SUMMARIZATION) {
            return "[GGUF Backend]: Summary of \"" + task.textInput + "\" using " + m_modelPath;
        }
        return "[GGUF Backend]: Task processed using " + m_modelPath;
    }

    std::string getName() const override { return "GGUF"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_GGUF_BACKEND_H
