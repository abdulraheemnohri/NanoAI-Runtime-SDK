#include "workflow_engine.h"
#include <iostream>
namespace nanoai {
WorkflowEngine& WorkflowEngine::getInstance() { static WorkflowEngine instance; return instance; }
void WorkflowEngine::runPipeline(const std::vector<std::string>& models, const std::string& input) {
    std::cout << "WorkflowEngine: Starting pipeline..." << std::endl;
    for (const auto& m : models) std::cout << "WorkflowEngine: Processing with " << m << std::endl;
}
}
