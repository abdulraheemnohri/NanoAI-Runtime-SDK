#include "nanoai/runtime.h"
#include "../scheduler/parallel_scheduler.h"
#include "../hardware/hal.h"
#include "../agents/agent_framework.h"
#include "../agents/swarm_engine.h"
#include "../telemetry/telemetry_manager.h"
#include "../../cluster/node/cluster_manager.h"
#include "../../cluster/discovery/discovery_service.h"
#include "../../models/registry/model_registry.h"
#include "../plugins/plugin_manager.h"
#include "../security/security_manager.h"
#include "workflow_engine.h"
#include <iostream>
#include <memory>

namespace nanoai {

class NanoRuntime::Impl {
public:
    Impl() {
        hal::HardwareAbstractionLayer::getInstance().discoverHardware();
        ParallelScheduler::getInstance().run();

        // Register all built-in agents
        auto& am = agents::AgentManager::getInstance();
        am.registerAgent(std::make_unique<agents::CodingAgent>());
        am.registerAgent(std::make_unique<agents::ResearchAgent>());
        am.registerAgent(std::make_unique<agents::VisionAgent>());

        plugins::PluginManager::getInstance().loadPlugins("plugins/");
    }

    ~Impl() {
        ParallelScheduler::getInstance().stop();
        cluster::DiscoveryService::getInstance().stopDiscovery();
    }

    bool loadModel(const std::string& modelPath, const std::string& modelId) {
        security::SecurityManager::getInstance().enforceSandbox(modelId);
        models::ModelRegistry::getInstance().registerModel(modelId, modelPath);
        std::cout << "Runtime: Model [" << modelId << "] deployed to HAL." << std::endl;
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
        return "[v2] Task " + req.taskId + " scheduled on " + modelId;
    }

    std::string runSwarm(const std::string& taskName, const std::vector<std::string>& agents, const std::string& input) {
        agents::SwarmTask swarmTask;
        swarmTask.taskName = taskName;
        swarmTask.agentChain = agents;
        return agents::SwarmEngine::getInstance().executeSwarmTask(swarmTask, input);
    }

    std::string runWorkflow(const std::string& workflowJson, const std::string& input) {
        std::vector<PipelineNode> nodes = { {"p1", "llm", "OCR", {}}, {"p2", "llm", "TRANS", {"p1"}} };
        return WorkflowEngine::getInstance().runVisualWorkflow(nodes, input);
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
std::string NanoRuntime::runSwarm(const std::string& t, const std::vector<std::string>& a, const std::string& i) { return pimpl->runSwarm(t, a, i); }
std::string NanoRuntime::runWorkflow(const std::string& w, const std::string& i) { return pimpl->runWorkflow(w, i); }
std::string NanoRuntime::getRuntimeTelemetry() { return pimpl->getRuntimeTelemetry(); }
std::string NanoRuntime::getHardwareProfile() { return pimpl->getHardwareProfile(); }
std::string NanoRuntime::getClusterNodes() { return pimpl->getClusterNodes(); }

} // namespace nanoai
