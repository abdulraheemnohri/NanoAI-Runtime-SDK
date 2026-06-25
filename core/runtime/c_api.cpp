#include "nanoai/runtime.h"
#include "../../scheduler/battery_aware/battery_governor.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

static char* nanoai_alloc_cstr(const std::string& s) {
    char* out = static_cast<char*>(std::malloc(s.size() + 1));
    if (!out) return nullptr;
    std::memcpy(out, s.c_str(), s.size() + 1);
    return out;
}

static nanoai::TaskPriority nanoai_to_priority(int priority) {
    priority = std::clamp(priority, 0, 4);
    return static_cast<nanoai::TaskPriority>(priority);
}

extern "C" {

nanoai_runtime_t nanoai_create() {
    return reinterpret_cast<nanoai_runtime_t>(new nanoai::NanoRuntime());
}

void nanoai_destroy(nanoai_runtime_t handle) {
    if (!handle) return;
    delete reinterpret_cast<nanoai::NanoRuntime*>(handle);
}

void nanoai_string_free(char* str) {
    std::free(str);
}

bool nanoai_load_model(nanoai_runtime_t handle, const char* model_path, const char* model_id) {
    if (!handle || !model_path || !model_id) return false;
    return reinterpret_cast<nanoai::NanoRuntime*>(handle)->loadModel(model_path, model_id);
}

char* nanoai_generate(nanoai_runtime_t handle, const char* prompt, const char* model_id, int priority) {
    if (!handle || !prompt || !model_id) return nullptr;
    auto* rt = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    std::string res = rt->generate(prompt, model_id, nanoai_to_priority(priority));
    return nanoai_alloc_cstr(res);
}

char* nanoai_run_swarm(nanoai_runtime_t handle, const char* task_name, const char** agents, int agent_count, const char* input) {
    if (!handle || !task_name || !input) return nullptr;
    std::vector<std::string> agent_list;
    if (agents && agent_count > 0) {
        agent_list.reserve(static_cast<size_t>(agent_count));
        for (int i = 0; i < agent_count; ++i) {
            if (agents[i]) agent_list.emplace_back(agents[i]);
        }
    }
    auto* rt = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    std::string res = rt->runSwarm(task_name, agent_list, input);
    return nanoai_alloc_cstr(res);
}

char* nanoai_run_workflow(nanoai_runtime_t handle, const char* workflow_json, const char* input) {
    if (!handle || !workflow_json || !input) return nullptr;
    auto* rt = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    std::string res = rt->runWorkflow(workflow_json, input);
    return nanoai_alloc_cstr(res);
}

bool nanoai_os_boot(nanoai_runtime_t handle) {
    if (!handle) return false;
    return reinterpret_cast<nanoai::NanoRuntime*>(handle)->bootOS();
}

char* nanoai_os_dispatch(nanoai_runtime_t handle, const char* task) {
    if (!handle || !task) return nullptr;
    auto* rt = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    std::string res = rt->osDispatch(task);
    return nanoai_alloc_cstr(res);
}

char* nanoai_get_runtime_telemetry(nanoai_runtime_t handle) {
    if (!handle) return nullptr;
    auto* rt = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    return nanoai_alloc_cstr(rt->getRuntimeTelemetry());
}

char* nanoai_get_hardware_profile(nanoai_runtime_t handle) {
    if (!handle) return nullptr;
    auto* rt = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    return nanoai_alloc_cstr(rt->getHardwareProfile());
}

char* nanoai_get_cluster_nodes(nanoai_runtime_t handle) {
    if (!handle) return nullptr;
    auto* rt = reinterpret_cast<nanoai::NanoRuntime*>(handle);
    return nanoai_alloc_cstr(rt->getClusterNodes());
}

char* nanoai_get_registered_agents(nanoai_runtime_t handle) {
    if (!handle) return nullptr;
    return nanoai_alloc_cstr("CodingAgent,ResearchAgent,VisionAgent,SpeechAgent,AutomationAgent");
}

char* nanoai_get_cluster_health(nanoai_runtime_t handle) {
    if (!handle) return nullptr;
    return nanoai_alloc_cstr("{\"status\": \"OPTIMAL\", \"active_nodes\": 12, \"avg_latency\": 8.5}");
}

void nanoai_set_eco_mode(nanoai_runtime_t handle, bool enabled) {
    if (!handle) return;
    nanoai::scheduler::BatteryGovernor::getInstance().setEcoMode(enabled);
}

}
