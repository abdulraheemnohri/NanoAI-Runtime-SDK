#include "agent_framework.h"
#include <algorithm>
namespace nanoai { namespace agents {
AgentManager& AgentManager::getInstance() { static AgentManager instance; return instance; }
void AgentManager::registerAgent(std::unique_ptr<AiAgent> agent) { m_agents.push_back(std::move(agent)); }
std::string AgentManager::execute(const std::string& name, const std::string& input) {
    for (auto& a : m_agents) if (a->getName() == name) return a->run(input);
    return "Agent not found.";
}
} }
