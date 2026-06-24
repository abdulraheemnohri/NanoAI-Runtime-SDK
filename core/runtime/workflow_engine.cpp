#include "workflow_engine.h"
#include <iostream>

namespace nanoai {

WorkflowEngine& WorkflowEngine::getInstance() {
    static WorkflowEngine instance;
    return instance;
}

std::string WorkflowEngine::runVisualWorkflow(const std::vector<PipelineNode>& nodes, const std::string& initialInput) {
    std::cout << "WorkflowEngine: Executing visual pipeline (" << nodes.size() << " nodes)" << std::endl;
    std::string data = initialInput;
    for (const auto& node : nodes) {
        std::cout << "WorkflowEngine: Executing " << node.operation << " on " << node.modelId << std::endl;
        data = "[" + node.operation + "] " + data;
    }
    return data;
}

} // namespace nanoai
