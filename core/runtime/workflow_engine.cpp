#include "workflow_engine.h"
#include <iostream>
#include <map>

namespace nanoai {

WorkflowEngine& WorkflowEngine::getInstance() {
    static WorkflowEngine instance;
    return instance;
}

std::string WorkflowEngine::executePipeline(const std::vector<PipelineNode>& nodes, const std::string& initialData) {
    std::cout << "WorkflowEngine: Starting visual pipeline execution..." << std::endl;

    std::string currentData = initialData;
    std::map<std::string, const PipelineNode*> nodeMap;
    for(const auto& n : nodes) nodeMap[n.id] = &n;

    for (const auto& node : nodes) {
        std::string opName;
        switch(node.type) {
            case NodeType::INPUT_CAMERA: opName = "Camera Feed"; break;
            case NodeType::TASK_OCR: opName = "OCR Processing"; break;
            case NodeType::TASK_TRANSLATE: opName = "Translation"; break;
            case NodeType::TASK_SUMMARIZE: opName = "Summarization"; break;
            case NodeType::OUTPUT_VOICE: opName = "Speech Synthesis"; break;
            default: opName = "Generic Task";
        }

        std::cout << "WorkflowEngine: [Step " << node.id << "] " << opName << " using " << node.modelId << std::endl;
        currentData = "[" + opName + " result] " + currentData;
    }

    std::cout << "WorkflowEngine: Pipeline finished successfully." << std::endl;
    return currentData;
}

} // namespace nanoai
