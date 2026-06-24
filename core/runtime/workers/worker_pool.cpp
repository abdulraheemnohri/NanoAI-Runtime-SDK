#include "worker_pool.h"

namespace nanoai {
namespace engine {

WorkerPool& WorkerPool::getInstance() {
    static WorkerPool instance;
    return instance;
}

void WorkerPool::initialize(int size) {
    for (int i = 0; i < size; ++i) {
        auto w = std::make_unique<InferenceWorker>(i);
        w->start();
        m_workers.push_back(std::move(w));
    }
}

void WorkerPool::submit(const InferenceTask& task) {
    if (m_workers.empty()) return;
    static size_t idx = 0;
    m_workers[idx++ % m_workers.size()]->addTask(task);
}

} }
