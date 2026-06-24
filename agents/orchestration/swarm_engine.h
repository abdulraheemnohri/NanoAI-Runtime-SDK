#ifndef NANOAI_SWARM_ENGINE_H
#define NANOAI_SWARM_ENGINE_H

#include <string>
#include <vector>
#include <memory>
#include "agent_framework.h"

namespace nanoai {
namespace agents {

struct SwarmTask {
    std::string taskName;
    std::vector<std::string> agentChain; // e.g., {"ResearchAgent", "CodingAgent", "VisionAgent"}
};

class SwarmEngine {
public:
    static SwarmEngine& getInstance();
    std::string executeSwarmTask(const SwarmTask& swarmTask, const std::string& input);
};

} // namespace agents
} // namespace nanoai

#endif // NANOAI_SWARM_ENGINE_H
