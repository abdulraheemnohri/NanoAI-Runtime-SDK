#include "../orchestration/agent_framework.h"
#include <iostream>

namespace nanoai { namespace agents {
class DeepResearchAgent : public AiAgent {
    std::string getName() const override { return "DeepResearchAgent"; }
    std::string run(const std::string& input) override { return "[DeepResearch] Multi-source analysis for: " + input; }
};
} }
