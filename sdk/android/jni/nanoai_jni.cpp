#include <jni.h>
#include <string>
#include <vector>
#include "nanoai/runtime.h"

extern "C" {

JNIEXPORT jlong JNICALL
Java_org_nanoai_NanoRuntime_nativeInit(JNIEnv* env, jobject thiz) {
    return reinterpret_cast<jlong>(new nanoai::NanoRuntime());
}

JNIEXPORT void JNICALL
Java_org_nanoai_NanoRuntime_nativeDestroy(JNIEnv* env, jobject thiz, jlong handle) {
    delete reinterpret_cast<nanoai::NanoRuntime*>(handle);
}

JNIEXPORT jboolean JNICALL
Java_org_nanoai_NanoRuntime_nativeLoadModel(JNIEnv* env, jobject thiz, jlong handle, jstring model_path, jstring model_id) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* path = env->GetStringUTFChars(model_path, nullptr);
    const char* id = env->GetStringUTFChars(model_id, nullptr);
    bool success = runtime->loadModel(path, id);
    env->ReleaseStringUTFChars(model_path, path);
    env->ReleaseStringUTFChars(model_id, id);
    return (jboolean)success;
}

JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGenerate(JNIEnv* env, jobject thiz, jlong handle, jstring prompt, jstring model_id, jint priority) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* input = env->GetStringUTFChars(prompt, nullptr);
    const char* id = env->GetStringUTFChars(model_id, nullptr);
    std::string result = runtime->generate(input, id, static_cast<nanoai::TaskPriority>(priority));
    env->ReleaseStringUTFChars(prompt, input);
    env->ReleaseStringUTFChars(model_id, id);
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeRunSwarm(JNIEnv* env, jobject thiz, jlong handle, jstring task_name, jobjectArray agents, jstring input) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* t_name = env->GetStringUTFChars(task_name, nullptr);
    const char* in = env->GetStringUTFChars(input, nullptr);
    int count = env->GetArrayLength(agents);
    std::vector<std::string> agentList;
    for(int i=0; i<count; ++i) {
        jstring agent = (jstring)env->GetObjectArrayElement(agents, i);
        const char* s = env->GetStringUTFChars(agent, nullptr);
        agentList.push_back(s);
        env->ReleaseStringUTFChars(agent, s);
    }
    std::string result = runtime->runSwarm(t_name, agentList, in);
    env->ReleaseStringUTFChars(task_name, t_name);
    env->ReleaseStringUTFChars(input, in);
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeRunWorkflow(JNIEnv* env, jobject thiz, jlong handle, jstring workflow_json, jstring input) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* w_json = env->GetStringUTFChars(workflow_json, nullptr);
    const char* in = env->GetStringUTFChars(input, nullptr);
    std::string result = runtime->runWorkflow(w_json, in);
    env->ReleaseStringUTFChars(workflow_json, w_json);
    env->ReleaseStringUTFChars(input, in);
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jboolean JNICALL
Java_org_nanoai_NanoRuntime_nativeBootOS(JNIEnv* env, jobject thiz, jlong handle) {
    return (jboolean)reinterpret_cast<nanoai::NanoRuntime*>(handle)->bootOS();
}

JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeOSDispatch(JNIEnv* env, jobject thiz, jlong handle, jstring task) {
    auto* runtime = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    const char* t = env->GetStringUTFChars(task, nullptr);
    std::string result = runtime->osDispatch(t);
    env->ReleaseStringUTFChars(task, t);
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGetTelemetry(JNIEnv* env, jobject thiz, jlong handle) {
    return env->NewStringUTF(reinterpret_cast<nanoai::NanoRuntime*>(handle)->getRuntimeTelemetry().c_str());
}

JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGetHardwareProfile(JNIEnv* env, jobject thiz, jlong handle) {
    return env->NewStringUTF(reinterpret_cast<nanoai::NanoRuntime*>(handle)->getHardwareProfile().c_str());
}

JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGetClusterNodes(JNIEnv* env, jobject thiz, jlong handle) {
    return env->NewStringUTF(reinterpret_cast<nanoai::NanoRuntime*>(handle)->getClusterNodes().c_str());
}

JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGetRegisteredAgents(JNIEnv* env, jobject thiz, jlong handle) {
    return env->NewStringUTF(nanoai_get_registered_agents(reinterpret_cast<nanoai_runtime_t>(handle)));
}

JNIEXPORT jstring JNICALL
Java_org_nanoai_NanoRuntime_nativeGetClusterHealth(JNIEnv* env, jobject thiz, jlong handle) {
    return env->NewStringUTF(nanoai_get_cluster_health(reinterpret_cast<nanoai_runtime_t>(handle)));
}

JNIEXPORT void JNICALL
Java_org_nanoai_NanoRuntime_nativeSetEcoMode(JNIEnv* env, jobject thiz, jlong handle, jboolean enabled) {
    nanoai_set_eco_mode(reinterpret_cast<nanoai_runtime_t>(handle), (bool)enabled);
}

}
