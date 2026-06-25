#include "parallel_scheduler.h"
#include "../../hardware/discovery/hal.h"
#include "../../../cluster/discovery/discovery.h"
#include "../../../scheduler/thermal_aware/thermal_governor.h"
#include "../../../scheduler/battery_aware/battery_governor.h"
#include <iostream>
#include <chrono>
#include <algorithm>

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
    bool expected = false;
    if (!m_running.compare_exchange_strong(expected, true)) return;
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
        m_running.store(false);
    }
    m_cv.notify_all();
    for (auto& w : m_workers) if (w.joinable()) w.join();
    m_workers.clear();
    cluster::DiscoveryService::getInstance().stopDiscovery();
}

static float calculateDeviceScore(const hal::DeviceCapability& cap, float load) {
    float base = cap.performanceScore;
    float availability = 1.0f - load;

    float thermalFactor = scheduler::ThermalGovernor::getInstance().getThrottlingFactor();
    bool powerThrottling = scheduler::BatteryGovernor::getInstance().shouldThrottlingForPower();
    bool ecoMode = scheduler::BatteryGovernor::getInstance().isEcoModeEnabled();

    float score = base * availability * thermalFactor;

    // NRX Eco-Mode: Favor NPU/DSP over GPU/CPU
    if (ecoMode) {
        if (cap.category == hal::DeviceCategory::NPU || cap.category == hal::DeviceCategory::DSP) {
            score *= 2.0f; // Boost efficient hardware
        } else if (cap.category == hal::DeviceCategory::GPU || cap.category == hal::DeviceCategory::CPU) {
            score *= 0.3f; // Heavily penalize power-hungry hardware
        }
    } else if (powerThrottling) {
        score *= 0.5f;
    }

    return score;
}

void ParallelScheduler::workerThread() {
    while (true) {
        AiTaskRequest task;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_cv.wait(lock, [this] { return !m_taskQueue.empty() || !m_running.load(); });
            if (!m_running.load() && m_taskQueue.empty()) break;
            task = m_taskQueue.top();
            m_taskQueue.pop();
        }

        auto remoteNodes = cluster::DiscoveryService::getInstance().getDiscoveredNodes();
        bool processed = false;

        bool isThermalStressed = scheduler::ThermalGovernor::getInstance().isOverheating();
        bool ecoMode = scheduler::BatteryGovernor::getInstance().isEcoModeEnabled();

        // 1. Cluster Load Balancing (Prioritize if local stress or Eco-Mode)
        if (!remoteNodes.empty() && (task.priority != TaskPriority::CRITICAL || isThermalStressed || ecoMode)) {
            auto it = std::min_element(remoteNodes.begin(), remoteNodes.end(),
                [](const auto& a, const auto& b) { return a.currentLoad < b.currentLoad; });

            if (it->currentLoad < 0.5f) {
                std::cout << "Scheduler: [NRX-ECO-OFFLOAD] Target: " << it->id << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(150));
                processed = true;
            }
        }

        // 2. Hardware-Aware Local Scheduling
        if (!processed) {
            auto devices = hal::HardwareAbstractionLayer::getInstance().getAvailableDevices();
            std::shared_ptr<hal::HardwareDevice> bestDevice = nullptr;
            float bestScore = -1.0f;

            for (auto& d : devices) {
                float score = calculateDeviceScore(d->getCapability(), d->currentLoad());

                if (task.modelId.find("vision") != std::string::npos && d->getCapability().category == hal::DeviceCategory::GPU) score += 20.0f;
                if (task.modelId.find("chat") != std::string::npos && d->getCapability().category == hal::DeviceCategory::NPU) score += 20.0f;

                if (score > bestScore) {
                    bestScore = score;
                    bestDevice = d;
                }
            }

            if (bestDevice) {
                std::cout << "Scheduler: [NRX-EXEC] Task " << task.taskId << " -> " << bestDevice->getCapability().name
                          << " (NRX-Score: " << bestScore << ")" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
        }

        std::cout << "Scheduler: Task " << task.taskId << " finalized." << std::endl;
    }
}

} // namespace nanoai
