#include "runtime_engine.h"

namespace nanoai {
namespace engine {

RuntimeEngine& RuntimeEngine::getInstance() {
    static RuntimeEngine instance;
    return instance;
}

void RuntimeEngine::initialize(int workerCount) {
    for (int i = 0; i < workerCount; ++i) {
        auto worker = std::make_unique<InferenceWorker>(i);
        worker->start();
        m_workers.push_back(std::move(worker));
    }
}

void RuntimeEngine::shutdown() {
    for (auto& worker : m_workers) {
        worker->stop();
    }
    m_workers.clear();
}

void RuntimeEngine::submitTask(const InferenceTask& task) {
    // Simple round-robin for now
    static size_t current = 0;
    if (!m_workers.empty()) {
        m_workers[current % m_workers.size()]->addTask(task);
        current++;
    }
}

} // namespace engine
} // namespace nanoai
