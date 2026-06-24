#include "inference_worker.h"
#include <iostream>

namespace nanoai {
namespace engine {

InferenceWorker::InferenceWorker(int id) : m_id(id), m_running(false) {}

InferenceWorker::~InferenceWorker() {
    stop();
}

void InferenceWorker::start() {
    m_running = true;
    m_thread = std::thread(&InferenceWorker::workLoop, this);
    std::cout << "InferenceWorker [" << m_id << "]: Started." << std::endl;
}

void InferenceWorker::stop() {
    m_running = false;
    m_cv.notify_all();
    if (m_thread.joinable()) m_thread.join();
}

void InferenceWorker::addTask(const InferenceTask& task) {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_tasks.push(task);
    }
    m_cv.notify_one();
}

void InferenceWorker::workLoop() {
    while (m_running) {
        InferenceTask task;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock, [this] { return !m_tasks.empty() || !m_running; });
            if (!m_running && m_tasks.empty()) break;
            task = m_tasks.front();
            m_tasks.pop();
        }

        std::cout << "InferenceWorker [" << m_id << "]: Executing task " << task.taskId << "..." << std::endl;
        // Simulated execution
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "InferenceWorker [" << m_id << "]: Task " << task.taskId << " complete." << std::endl;
    }
}

} // namespace engine
} // namespace nanoai
