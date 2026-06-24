#ifndef NANOAI_AGENT_FRAMEWORK_H
#define NANOAI_AGENT_FRAMEWORK_H
#include <string>
#include <vector>
#include <memory>

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
    std::string run(const std::string& input) override { return "[Coding] Generating code for: " + input; }
};

class AgentManager {
public:
    static AgentManager& getInstance();
    void registerAgent(std::unique_ptr<AiAgent> agent);
    std::string execute(const std::string& agentName, const std::string& input);
private:
    std::vector<std::unique_ptr<AiAgent>> m_agents;
};
} }
#endif
