#include "workflow_engine.h"
#include <iostream>
namespace nanoai {
std::string WorkflowEngine::executePipeline(const std::vector<PipelineNode>& nodes, const std::string& initialData) {
    std::string data = initialData;
    for (const auto& node : nodes) {
        std::cout << "[PIPELINE] Executing " << node.id << " on " << node.modelId << std::endl;
        data = "[" + node.id + " result] " + data;
    }
    return data;
}
}
