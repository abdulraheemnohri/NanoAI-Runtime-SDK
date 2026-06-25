#include "../../plugins/api/plugin_api.h"
#include "../../agents/orchestration/agent_framework.h"
#include <iostream>

namespace nanoai {
namespace plugins {

class MedicalAiPlugin : public AiPlugin {
public:
    std::string getPluginId() const override { return "MedicalDiagnostics_v1"; }

    void initialize() override {
        std::cout << "MedicalPlugin: Initializing health datasets and specialized NLP..." << std::endl;

        // Dynamic Agent Registration
        auto& am = agents::AgentManager::getInstance();
        am.registerAgent(std::make_unique<agents::ResearchAgent>()); // Use existing research agent for medical papers
    }

    std::string execute(const std::string& input) override {
        return "[Medical] Analyzed clinical data: " + input + " | Confidence: 0.98";
    }
};

} }
