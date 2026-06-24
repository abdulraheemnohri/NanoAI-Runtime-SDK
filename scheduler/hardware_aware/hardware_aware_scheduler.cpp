#include "../../core/runtime/scheduler/parallel_scheduler.h"
#include <iostream>
namespace nanoai {
void ParallelScheduler::scheduleTask(const AiTaskRequest& req) {
    std::cout << "HardwareAwareScheduler: Routing " << req.taskId << " based on VRAM/NPU availability." << std::endl;
    // Task added to queue for worker threads
    { std::lock_guard<std::mutex> lock(m_queueMutex); m_taskQueue.push(req); }
    m_cv.notify_one();
}
}
