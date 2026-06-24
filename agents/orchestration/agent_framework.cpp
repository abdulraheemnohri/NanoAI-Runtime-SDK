#include "agent_framework.h"
#include <algorithm>

namespace nanoai {
namespace agents {

AgentManager& AgentManager::getInstance() {
    static AgentManager instance;
    return instance;
}

void AgentManager::registerAgent(std::unique_ptr<AiAgent> agent) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_agents.push_back(std::move(agent));
}

std::string AgentManager::execute(const std::string& name, const std::string& input) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& a : m_agents) {
        if (a->getName() == name) return a->run(input);
    }
    return "Agent not found: " + name;
}

std::vector<std::string> AgentManager::getRegisteredAgents() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<std::string> names;
    for (auto& a : m_agents) names.push_back(a->getName());
    return names;
}

} // namespace agents
} // namespace nanoai
