#include <jni.h>
#include <string>
#include "nanoai/runtime.h"

extern "C" JNIEXPORT jlong JNICALL
Java_org_nanoai_NanoRuntime_nativeInit(JNIEnv* env, jobject thiz) {
    return reinterpret_cast<jlong>(new nanoai::NanoRuntime());
}

extern "C" JNIEXPORT void JNICALL
Java_org_nanoai_NanoRuntime_nativeDestroy(JNIEnv* env, jobject thiz, jlong handle) {
    delete reinterpret_cast<nanoai::NanoRuntime*>(handle);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_nanoai_NanoRuntime_nativeLoadModel(JNIEnv* env, jobject thiz, jlong handle, jstring model_path, jstring model_id) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* path = env->GetStringUTFChars(model_path, nullptr);
    const char* id = env->GetStringUTFChars(model_id, nullptr);
    bool success = runtime->loadModel(path, id);
    env->ReleaseStringUTFChars(model_path, path);
    env->ReleaseStringUTFChars(model_id, id);
    return static_cast<jboolean>(success);
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGenerate(JNIEnv* env, jobject thiz, jlong handle, jstring prompt, jstring model_id, jint priority) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* input = env->GetStringUTFChars(prompt, nullptr);
    const char* id = env->GetStringUTFChars(model_id, nullptr);
    std::string result = runtime->generate(input, id, static_cast<nanoai::TaskPriority>(priority));
    env->ReleaseStringUTFChars(prompt, input);
    env->ReleaseStringUTFChars(model_id, id);
    return env->NewStringUTF(result.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGetTelemetry(JNIEnv* env, jobject thiz, jlong handle) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    return env->NewStringUTF(runtime->getRuntimeTelemetry().c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGetHardwareProfile(JNIEnv* env, jobject thiz, jlong handle) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    return env->NewStringUTF(runtime->getHardwareProfile().c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGetClusterNodes(JNIEnv* env, jobject thiz, jlong handle) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    return env->NewStringUTF(runtime->getClusterNodes().c_str());
}
