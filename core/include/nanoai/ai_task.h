#ifndef NANOAI_AI_TASK_H
#define NANOAI_AI_TASK_H

#include <vector>
#include <string>
#include <cstdint>

namespace nanoai {

enum class TaskType {
    TEXT_GENERATION,
    TEXT_SUMMARIZATION,
    VISION_OCR,
    VISION_OBJECT_DETECTION,
    VISION_SEGMENTATION,
    VISION_FACE_ANALYSIS,
    AUDIO_SPEECH_RECOGNITION,
    AUDIO_VOICE_COMMANDS,
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
