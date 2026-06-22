#include "nanoai/runtime.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    nanoai::NanoRuntime runtime;

    // Test OCR Task (Vision)
    runtime.loadModel("vision_model.onnx");
    std::vector<uint8_t> dummy_image(100 * 100 * 3, 0);
    nanoai::AiTask vision_task;
    vision_task.type = nanoai::TaskType::VISION_OCR;
    vision_task.visionInput = {dummy_image, 100, 100, 3};
    std::string ocr_result = runtime.runTask(vision_task);
    std::cout << "OCR Result: " << ocr_result << std::endl;
    assert(ocr_result.find("[ONNX Backend]: OCR complete") != std::string::npos);

    // Test Wake Word Task (Audio)
    runtime.loadModel("audio_model.tflite");
    std::vector<float> dummy_audio(16000, 0.0f);
    nanoai::AiTask audio_task;
    audio_task.type = nanoai::TaskType::AUDIO_WAKE_WORD;
    audio_task.audioInput = {dummy_audio, 16000};
    std::string audio_result = runtime.runTask(audio_task);
    std::cout << "Audio Result: " << audio_result << std::endl;
    assert(audio_result.find("[TFLite Backend]: Wake word detected") != std::string::npos);

    std::cout << "Multi-modal AI Task Test Passed!" << std::endl;
    return 0;
}
