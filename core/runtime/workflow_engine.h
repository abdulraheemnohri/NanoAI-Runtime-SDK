#ifndef NANOAI_WORKFLOW_ENGINE_H
#define NANOAI_WORKFLOW_ENGINE_H
#include <string>
#include <vector>
namespace nanoai {
class WorkflowEngine {
public:
    static WorkflowEngine& getInstance();
    void runPipeline(const std::vector<std::string>& models, const std::string& input);
};
}
#endif
