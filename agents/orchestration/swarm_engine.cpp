#include "swarm_engine.h"
#include "agent_framework.h"
#include <iostream>

namespace nanoai {
namespace agents {

SwarmEngine& SwarmEngine::getInstance() {
    static SwarmEngine instance;
    return instance;
}

std::string SwarmEngine::executeSwarmTask(const SwarmTask& swarmTask, const std::string& input) {
    std::cout << "SwarmEngine: Initiating collaborative task [" << swarmTask.taskName << "]" << std::endl;
    std::string currentResult = input;

    for (const auto& agentName : swarmTask.agentChain) {
        std::cout << "SwarmEngine: Routing to " << agentName << "..." << std::endl;
        currentResult = AgentManager::getInstance().execute(agentName, currentResult);
    }

    std::cout << "SwarmEngine: Collaborative task complete." << std::endl;
    return currentResult;
}

} // namespace agents
} // namespace nanoai
