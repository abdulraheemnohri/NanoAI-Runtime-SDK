#ifndef NANOAI_WORKFLOW_ENGINE_H
#define NANOAI_WORKFLOW_ENGINE_H

#include <string>
#include <vector>
#include <map>

namespace nanoai {

struct PipelineNode {
    std::string id;
    std::string modelId;
    std::string operation; // OCR, TRANSLATE, etc.
    std::vector<std::string> dependencies;
};

class WorkflowEngine {
public:
    static WorkflowEngine& getInstance();
    std::string runVisualWorkflow(const std::vector<PipelineNode>& nodes, const std::string& initialInput);
};

} // namespace nanoai

#endif // NANOAI_WORKFLOW_ENGINE_H
