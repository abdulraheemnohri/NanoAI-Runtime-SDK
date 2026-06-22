#include <jni.h>
#include <string>
#include <vector>
#include "nanoai/runtime.h"

extern "C" JNIEXPORT jlong JNICALL
Java_org_nanoai_NanoRuntime_nativeInit(JNIEnv* env, jobject thiz) {
    auto* runtime = new nanoai::NanoRuntime();
    return reinterpret_cast<jlong>(runtime);
}

extern "C" JNIEXPORT void JNICALL
Java_org_nanoai_NanoRuntime_nativeDestroy(JNIEnv* env, jobject thiz, jlong handle) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    delete runtime;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_nanoai_NanoRuntime_nativeLoadModel(JNIEnv* env, jobject thiz, jlong handle, jstring model_path) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* path = env->GetStringUTFChars(model_path, nullptr);
    bool success = runtime->loadModel(path);
    env->ReleaseStringUTFChars(model_path, path);
    return static_cast<jboolean>(success);
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGenerate(JNIEnv* env, jobject thiz, jlong handle, jstring prompt) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* input = env->GetStringUTFChars(prompt, nullptr);
    std::string result = runtime->generate(input);
    env->ReleaseStringUTFChars(prompt, input);
    return env->NewStringUTF(result.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeRunOCR(JNIEnv* env, jobject thiz, jlong handle, jbyteArray buffer, jint width, jint height) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    jbyte* bytes = env->GetByteArrayElements(buffer, nullptr);
    jsize len = env->GetArrayLength(buffer);

    nanoai::AiTask task;
    task.type = nanoai::TaskType::VISION_OCR;
    task.visionInput = {std::vector<uint8_t>((uint8_t*)bytes, (uint8_t*)bytes + len), width, height, 3};

    std::string result = runtime->runTask(task);
    env->ReleaseByteArrayElements(buffer, bytes, JNI_ABORT);
    return env->NewStringUTF(result.c_str());
}
