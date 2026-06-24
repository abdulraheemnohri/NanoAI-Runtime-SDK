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

// Model Management
bool nanoai_load_model(nanoai_runtime_t handle, const char* model_path, const char* model_id);

// Parallel Execution API
const char* nanoai_generate(nanoai_runtime_t handle, const char* prompt, const char* model_id, int priority);

// Telemetry & Discovery
const char* nanoai_get_runtime_telemetry(nanoai_runtime_t handle);
const char* nanoai_get_hardware_profile(nanoai_runtime_t handle);
const char* nanoai_get_cluster_nodes(nanoai_runtime_t handle);

#ifdef __cplusplus
} // extern "C"

namespace nanoai {

enum class TaskPriority {
    CRITICAL = 0,
    HIGH = 1,
    NORMAL = 2,
    BACKGROUND = 3,
    IDLE = 4
};

class NanoRuntime {
public:
    NanoRuntime();
    ~NanoRuntime();

    bool loadModel(const std::string& modelPath, const std::string& modelId);
    std::string generate(const std::string& prompt, const std::string& modelId, TaskPriority priority = TaskPriority::NORMAL);

    std::string getRuntimeTelemetry();
    std::string getHardwareProfile();
    std::string getClusterNodes();

    class Impl;
private:
    std::unique_ptr<Impl> pimpl;
};

} // namespace nanoai
#endif

#endif // NANOAI_RUNTIME_H
