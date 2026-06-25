#ifndef NANOAI_RUNTIME_H
#define NANOAI_RUNTIME_H

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* nanoai_runtime_t;

nanoai_runtime_t nanoai_create();
void nanoai_destroy(nanoai_runtime_t handle);
void nanoai_string_free(char* str);

bool nanoai_load_model(nanoai_runtime_t handle, const char* model_path, const char* model_id);
char* nanoai_generate(nanoai_runtime_t handle, const char* prompt, const char* model_id, int priority);
char* nanoai_run_swarm(nanoai_runtime_t handle, const char* task_name, const char** agents, int agent_count, const char* input);
char* nanoai_run_workflow(nanoai_runtime_t handle, const char* workflow_json, const char* input);

bool nanoai_os_boot(nanoai_runtime_t handle);
char* nanoai_os_dispatch(nanoai_runtime_t handle, const char* task);

char* nanoai_get_runtime_telemetry(nanoai_runtime_t handle);
char* nanoai_get_hardware_profile(nanoai_runtime_t handle);
char* nanoai_get_cluster_nodes(nanoai_runtime_t handle);

#ifdef __cplusplus
} // extern "C"

namespace nanoai {

enum class TaskPriority { CRITICAL = 0, HIGH = 1, NORMAL = 2, BACKGROUND = 3, IDLE = 4 };

struct AiTaskRequest {
    std::string taskId;
    std::string modelId;
    std::string prompt;
    TaskPriority priority;
};

class NanoRuntime {
public:
    NanoRuntime();
    ~NanoRuntime();
    bool loadModel(const std::string& modelPath, const std::string& modelId);
    std::string generate(const std::string& prompt, const std::string& modelId, TaskPriority priority = TaskPriority::NORMAL);
    std::string runSwarm(const std::string& taskName, const std::vector<std::string>& agents, const std::string& input);
    std::string runWorkflow(const std::string& workflowJson, const std::string& input);
    bool bootOS();
    std::string osDispatch(const std::string& task);
    std::string getRuntimeTelemetry();
    std::string getHardwareProfile();
    std::string getClusterNodes();
    class Impl;
private:
    std::unique_ptr<Impl> pimpl;
};
}
#endif
#endif
