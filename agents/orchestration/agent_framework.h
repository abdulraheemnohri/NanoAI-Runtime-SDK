#ifndef NANOAI_AGENT_FRAMEWORK_H
#define NANOAI_AGENT_FRAMEWORK_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>

namespace nanoai {
namespace agents {

class AiAgent {
public:
    virtual ~AiAgent() = default;
    virtual std::string getName() const = 0;
    virtual std::string run(const std::string& input) = 0;
};

class CodingAgent : public AiAgent {
public:
    std::string getName() const override { return "CodingAgent"; }
    std::string run(const std::string& input) override { return "[Coding] Optimized logic for: " + input; }
};

class ResearchAgent : public AiAgent {
public:
    std::string getName() const override { return "ResearchAgent"; }
    std::string run(const std::string& input) override { return "[Research] Found data relevant to: " + input; }
};

class VisionAgent : public AiAgent {
public:
    std::string getName() const override { return "VisionAgent"; }
    std::string run(const std::string& input) override { return "[Vision] Object map for: " + input; }
};

// New specialized agents
class SpeechAgent : public AiAgent {
public:
    std::string getName() const override { return "SpeechAgent"; }
    std::string run(const std::string& input) override { return "[Speech] Transcribed text: " + input; }
};

class AutomationAgent : public AiAgent {
public:
    std::string getName() const override { return "AutomationAgent"; }
    std::string run(const std::string& input) override { return "[Automation] Executing workflow: " + input; }
};

class AgentManager {
public:
    static AgentManager& getInstance();
    void registerAgent(std::unique_ptr<AiAgent> agent);
    std::string execute(const std::string& agentName, const std::string& input);
    std::vector<std::string> getRegisteredAgents() const;

private:
    AgentManager() = default;
    std::vector<std::unique_ptr<AiAgent>> m_agents;
    mutable std::mutex m_mutex;
};

} // namespace agents
} // namespace nanoai

#endif // NANOAI_AGENT_FRAMEWORK_H
