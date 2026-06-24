#include "parallel_scheduler.h"
#include "../hardware/hal.h"
#include "../../cluster/discovery/discovery_service.h"
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
    cluster::DiscoveryService::getInstance().startDiscovery();
    int threads = std::thread::hardware_concurrency();
    if (threads == 0) threads = 4;
    for (int i = 0; i < threads; ++i) {
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
    cluster::DiscoveryService::getInstance().stopDiscovery();
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

        // DYNAMIC SCHEDULING LOGIC
        auto remoteNodes = cluster::DiscoveryService::getInstance().getDiscoveredNodes();
        bool offloaded = false;

        // If local load is high and remote node available with low load, offload
        if (!remoteNodes.empty() && remoteNodes[0].currentLoad < 0.3f && task.priority != TaskPriority::CRITICAL) {
            std::cout << "Scheduler: Offloading " << task.taskId << " to remote cluster node " << remoteNodes[0].id << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Network latency simulation
            offloaded = true;
        }

        if (!offloaded) {
            auto device = hal::HardwareAbstractionLayer::getInstance().getBestDeviceForTask(task.modelId.find("vision") != std::string::npos ? "VISION" : "LLM", 0);
            std::cout << "ParallelScheduler: Executing " << task.taskId << " on local " << device->getCapability().name << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        std::cout << "ParallelScheduler: " << task.taskId << " completed." << std::endl;
    }
}

} // namespace nanoai
