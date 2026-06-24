#include "parallel_scheduler.h"
#include "../hardware/hal.h"
#include <iostream>
#include <chrono>

namespace nanoai {

ParallelScheduler::ParallelScheduler() : m_running(false) {}
ParallelScheduler::~ParallelScheduler() { stop(); }

ParallelScheduler& ParallelScheduler::getInstance() {
    static ParallelScheduler instance;
    return instance;
}

void ParallelScheduler::scheduleTask(const AiTaskRequest& request) {
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_taskQueue.push(request);
    }
    m_cv.notify_one();
}

void ParallelScheduler::run() {
    if (m_running) return;
    m_running = true;
    for (int i = 0; i < 4; ++i) {
        m_workers.emplace_back(&ParallelScheduler::workerThread, this);
    }
}

void ParallelScheduler::stop() {
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_running = false;
    }
    m_cv.notify_all();
    for (auto& w : m_workers) if (w.joinable()) w.join();
    m_workers.clear();
}

void ParallelScheduler::workerThread() {
    while (true) {
        AiTaskRequest task;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_cv.wait(lock, [this] { return !m_taskQueue.empty() || !m_running; });
            if (!m_running && m_taskQueue.empty()) break;
            task = m_taskQueue.top();
            m_taskQueue.pop();
        }

        auto device = hal::HardwareAbstractionLayer::getInstance().getBestDeviceForTask("DEFAULT", 0);
        std::cout << "ParallelScheduler: Executing " << task.taskId << " on " << device->getCapability().name << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "ParallelScheduler: " << task.taskId << " finished." << std::endl;
    }
}

} // namespace nanoai
