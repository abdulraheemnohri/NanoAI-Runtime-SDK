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
Java_org_nanoai_NanoRuntime_nativeGenerate(JNIEnv* env, jobject thiz, jlong handle, jstring prompt, jstring model_id) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* input = env->GetStringUTFChars(prompt, nullptr);
    const char* id = env->GetStringUTFChars(model_id, nullptr);
    std::string result = runtime->generate(input, id);
    env->ReleaseStringUTFChars(prompt, input);
    env->ReleaseStringUTFChars(model_id, id);
    return env->NewStringUTF(result.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeSummarizeText(JNIEnv* env, jobject thiz, jlong handle, jstring text) {
    const char* input = env->GetStringUTFChars(text, nullptr);
    const char* result = nanoai_summarize_text(reinterpret_cast<nanoai_runtime_t>(handle), input);
    env->ReleaseStringUTFChars(text, input);
    return env->NewStringUTF(result);
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeRunOCR(JNIEnv* env, jobject thiz, jlong handle, jbyteArray buffer, jint width, jint height) {
    jbyte* bytes = env->GetByteArrayElements(buffer, nullptr);
    const char* result = nanoai_run_ocr(reinterpret_cast<nanoai_runtime_t>(handle), (uint8_t*)bytes, width, height);
    env->ReleaseByteArrayElements(buffer, bytes, JNI_ABORT);
    return env->NewStringUTF(result);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_nanoai_NanoRuntime_nativeConvertModel(JNIEnv* env, jclass clazz, jstring input_path, jstring output_path, jint quantization_type) {
    const char* in = env->GetStringUTFChars(input_path, nullptr);
    const char* out = env->GetStringUTFChars(output_path, nullptr);
    bool success = nanoai_convert_model(in, out, quantization_type);
    env->ReleaseStringUTFChars(input_path, in);
    env->ReleaseStringUTFChars(output_path, out);
    return static_cast<jboolean>(success);
}
