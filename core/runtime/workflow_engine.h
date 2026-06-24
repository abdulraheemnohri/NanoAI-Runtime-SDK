#ifndef NANOAI_WORKFLOW_ENGINE_H
#define NANOAI_WORKFLOW_ENGINE_H

#include <string>
#include <vector>
#include <functional>

namespace nanoai {

enum class NodeType {
    INPUT_CAMERA,
    INPUT_AUDIO,
    TASK_OCR,
    TASK_TRANSLATE,
    TASK_SUMMARIZE,
    TASK_GENERATE,
    OUTPUT_VOICE,
    OUTPUT_UI
};

struct PipelineNode {
    std::string id;
    NodeType type;
    std::string modelId;
    std::vector<std::string> nextNodes;
};

class WorkflowEngine {
public:
    static WorkflowEngine& getInstance();

    std::string executePipeline(const std::vector<PipelineNode>& nodes, const std::string& initialData);
};

} // namespace nanoai

#endif // NANOAI_WORKFLOW_ENGINE_H
