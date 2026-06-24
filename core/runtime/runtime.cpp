#include "nanoai/runtime.h"
#include "../scheduler/parallel_scheduler.h"
#include "../hardware/hal.h"
#include "../agents/agent_framework.h"
#include "../telemetry/telemetry_manager.h"
#include "../../cluster/node/cluster_manager.h"
#include "../../cluster/discovery/discovery_service.h"
#include "../../models/registry/model_registry.h"
#include "../plugins/plugin_manager.h"
#include "../security/security_manager.h"
#include <iostream>
#include <memory>

namespace nanoai {

class NanoRuntime::Impl {
public:
    Impl() {
        hal::HardwareAbstractionLayer::getInstance().discoverHardware();
        ParallelScheduler::getInstance().run();
        agents::AgentManager::getInstance().registerAgent(std::make_unique<agents::CodingAgent>());
        plugins::PluginManager::getInstance().loadPlugins("plugins/");
    }

    ~Impl() {
        ParallelScheduler::getInstance().stop();
        cluster::DiscoveryService::getInstance().stopDiscovery();
    }

    bool loadModel(const std::string& modelPath, const std::string& modelId) {
        security::SecurityManager::getInstance().enforceSandbox(modelId);
        models::ModelRegistry::getInstance().registerModel(modelId, modelPath);
        std::cout << "Runtime: Registered " << modelId << " at " << modelPath << std::endl;
        return true;
    }

    std::string generate(const std::string& prompt, const std::string& modelId, TaskPriority priority) {
        if (!security::SecurityManager::getInstance().validateAccess(modelId, "local_resource")) {
            return "Security Error: Access Denied.";
        }
        if (prompt.find("agent:") == 0) {
            return agents::AgentManager::getInstance().execute(modelId, prompt.substr(6));
        }
        AiTaskRequest req{ "t_" + std::to_string(m_counter++), modelId, prompt, priority };
        ParallelScheduler::getInstance().scheduleTask(req);
        return "[v2] Task " + req.taskId + " distributed to hardware cluster.";
    }

    std::string getRuntimeTelemetry() { return telemetry::TelemetryManager::getInstance().getFullReport(); }
    std::string getHardwareProfile() { return hal::HardwareAbstractionLayer::getInstance().generateCapabilityProfile(); }
    std::string getClusterNodes() { return cluster::ClusterManager::getInstance().getNodes(); }

private:
    int m_counter = 0;
};

NanoRuntime::NanoRuntime() : pimpl(std::make_unique<Impl>()) {}
NanoRuntime::~NanoRuntime() = default;
bool NanoRuntime::loadModel(const std::string& p, const std::string& i) { return pimpl->loadModel(p, i); }
std::string NanoRuntime::generate(const std::string& pr, const std::string& id, TaskPriority pt) { return pimpl->generate(pr, id, pt); }
std::string NanoRuntime::getRuntimeTelemetry() { return pimpl->getRuntimeTelemetry(); }
std::string NanoRuntime::getHardwareProfile() { return pimpl->getHardwareProfile(); }
std::string NanoRuntime::getClusterNodes() { return pimpl->getClusterNodes(); }

} // namespace nanoai

extern "C" {
nanoai_runtime_t nanoai_create() { return new nanoai::NanoRuntime(); }
void nanoai_destroy(nanoai_runtime_t handle) { delete static_cast<nanoai::NanoRuntime*>(handle); }
bool nanoai_load_model(nanoai_runtime_t handle, const char* p, const char* i) { return static_cast<nanoai::NanoRuntime*>(handle)->loadModel(p, i); }
const char* nanoai_generate(nanoai_runtime_t handle, const char* pr, const char* id, int pt) {
    static thread_local std::string r;
    r = static_cast<nanoai::NanoRuntime*>(handle)->generate(pr, id, static_cast<nanoai::TaskPriority>(pt));
    return r.c_str();
}
const char* nanoai_get_runtime_telemetry(nanoai_runtime_t handle) {
    static thread_local std::string r; r = static_cast<nanoai::NanoRuntime*>(handle)->getRuntimeTelemetry(); return r.c_str();
}
const char* nanoai_get_hardware_profile(nanoai_runtime_t handle) {
    static thread_local std::string r; r = static_cast<nanoai::NanoRuntime*>(handle)->getHardwareProfile(); return r.c_str();
}
const char* nanoai_get_cluster_nodes(nanoai_runtime_t handle) {
    static thread_local std::string r; r = static_cast<nanoai::NanoRuntime*>(handle)->getClusterNodes(); return r.c_str();
}
}
