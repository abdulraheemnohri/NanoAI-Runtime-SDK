#ifndef NANOAI_AI_TASK_H
#define NANOAI_AI_TASK_H

#include <vector>
#include <string>
#include <cstdint>

namespace nanoai {

enum class TaskType {
    TEXT_GENERATION,
    VISION_OCR,
    VISION_OBJECT_DETECTION,
    AUDIO_SPEECH_RECOGNITION,
    AUDIO_WAKE_WORD
};

struct VisionData {
    std::vector<uint8_t> buffer;
    int width;
    int height;
    int channels;
};

struct AudioData {
    std::vector<float> samples;
    int sampleRate;
};

struct AiTask {
    TaskType type;
    std::string textInput;
    VisionData visionInput;
    AudioData audioInput;
};

} // namespace nanoai

#endif // NANOAI_AI_TASK_H
