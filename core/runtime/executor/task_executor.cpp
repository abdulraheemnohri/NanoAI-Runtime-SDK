#include "task_executor.h"
#include <iostream>

#ifdef __linux__
#include <sched.h>
#endif

namespace nanoai {
namespace engine {

TaskExecutor& TaskExecutor::getInstance() {
    static TaskExecutor instance;
    return instance;
}

void TaskExecutor::pinToCore(int cpuId) {
#ifdef __linux__
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpuId, &cpuset);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
    std::cout << "TaskExecutor: Thread pinned to CPU core " << cpuId << std::endl;
#else
    std::cout << "TaskExecutor: Core pinning not supported on this platform." << std::endl;
#endif
}

void TaskExecutor::executeWithContext(const std::string& taskId, const std::string& modelId) {
    std::cout << "TaskExecutor: Initializing low-level context for [" << taskId << "] using [" << modelId << "]" << std::endl;
}

} // namespace engine
} // namespace nanoai
