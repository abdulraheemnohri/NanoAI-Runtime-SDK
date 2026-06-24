#ifndef NANOAI_PARALLEL_SCHEDULER_H
#define NANOAI_PARALLEL_SCHEDULER_H

#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <vector>
#include "nanoai/runtime.h"

namespace nanoai {

struct AiTaskRequest {
    std::string taskId;
    std::string modelId;
    std::string prompt;
    TaskPriority priority;

    bool operator<(const AiTaskRequest& other) const {
        return static_cast<int>(priority) > static_cast<int>(other.priority);
    }
};

class ParallelScheduler {
public:
    static ParallelScheduler& getInstance();
    void scheduleTask(const AiTaskRequest& request);
    void run();
    void stop();

private:
    ParallelScheduler();
    ~ParallelScheduler();
    void workerThread();

    std::priority_queue<AiTaskRequest> m_taskQueue;
    std::mutex m_queueMutex;
    std::condition_variable m_cv;
    std::vector<std::thread> m_workers;
    bool m_running;
};

} // namespace nanoai
#endif
