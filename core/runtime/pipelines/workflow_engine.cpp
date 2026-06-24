#include "workflow_engine.h"
#include <iostream>
#include <map>
#include <sstream>

namespace nanoai {

WorkflowEngine& WorkflowEngine::getInstance() {
    static WorkflowEngine instance;
    return instance;
}

std::string WorkflowEngine::executePipeline(const std::vector<PipelineNode>& nodes, const std::string& initialData) {
    std::cout << "WorkflowEngine: Starting visual pipeline execution..." << std::endl;

    std::string currentData = initialData;

    // In a real implementation, this would use the graph structure (nextNodes)
    // for now we follow the order in the vector for simplicity.
    for (const auto& node : nodes) {
        std::string opName;
        switch(node.type) {
            case NodeType::INPUT_CAMERA: opName = "Camera Feed"; break;
            case NodeType::INPUT_AUDIO: opName = "Audio Input"; break;
            case NodeType::TASK_OCR: opName = "OCR Processing"; break;
            case NodeType::TASK_TRANSLATE: opName = "Translation"; break;
            case NodeType::TASK_SUMMARIZE: opName = "Summarization"; break;
            case NodeType::TASK_GENERATE: opName = "Text Generation"; break;
            case NodeType::OUTPUT_VOICE: opName = "Speech Synthesis"; break;
            case NodeType::OUTPUT_UI: opName = "UI Display"; break;
            default: opName = "Generic Task";
        }

        std::cout << "WorkflowEngine: [Step " << node.id << "] " << opName << " using " << node.modelId << std::endl;
        currentData = "[" + opName + " result] " + currentData;
    }

    std::cout << "WorkflowEngine: Pipeline finished successfully." << std::endl;
    return currentData;
}

// Simulated JSON parsing for the v2 demo
std::string WorkflowEngine::runFromJson(const std::string& json, const std::string& input) {
    std::cout << "WorkflowEngine: Parsing JSON workflow..." << std::endl;

    std::vector<PipelineNode> nodes;

    // Very simple "parser" for demonstration purposes
    if (json.find("ocr") != std::string::npos) {
        nodes.push_back({"n1", NodeType::TASK_OCR, "vision-model", {}});
    }
    if (json.find("translate") != std::string::npos) {
        nodes.push_back({"n2", NodeType::TASK_TRANSLATE, "llm-model", {}});
    }
    if (nodes.empty()) {
        nodes.push_back({"n0", NodeType::TASK_GENERATE, "default-model", {}});
    }

    return executePipeline(nodes, input);
}

} // namespace nanoai
