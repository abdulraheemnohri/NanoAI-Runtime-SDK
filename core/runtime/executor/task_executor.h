#ifndef NANOAI_TASK_EXECUTOR_H
#define NANOAI_TASK_EXECUTOR_H

#include <string>
#include <vector>

namespace nanoai {
namespace engine {

class TaskExecutor {
public:
    static TaskExecutor& getInstance();

    void pinToCore(int cpuId);
    void executeWithContext(const std::string& taskId, const std::string& modelId);
};

} // namespace engine
} // namespace nanoai

#endif // NANOAI_TASK_EXECUTOR_H
