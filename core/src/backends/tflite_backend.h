#ifndef NANOAI_TFLITE_BACKEND_H
#define NANOAI_TFLITE_BACKEND_H

#include "../backend.h"
#include <iostream>

namespace nanoai {

class TfLiteBackend : public Backend {
public:
    bool load(const std::string& modelPath) override {
        m_modelPath = modelPath;
        std::cout << "TFLite Backend: Initializing with " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt) override {
        return "[TFLite Backend]: Response to \"" + prompt + "\" using " + m_modelPath;
    }

    std::string runTask(const AiTask& task) override {
        if (task.type == TaskType::AUDIO_WAKE_WORD) {
            return "[TFLite Backend]: Wake word detected using " + m_modelPath;
        }
        return "[TFLite Backend]: Task processed";
    }

    std::string getName() const override { return "TFLite"; }

private:
    std::string m_modelPath;
};

} // namespace nanoai

#endif // NANOAI_TFLITE_BACKEND_H
