#ifndef NANOAI_WORKER_POOL_H
#define NANOAI_WORKER_POOL_H

#include "inference_worker.h"
#include <vector>
#include <memory>

namespace nanoai {
namespace engine {

class WorkerPool {
public:
    static WorkerPool& getInstance();
    void initialize(int size);
    void submit(const InferenceTask& task);

private:
    WorkerPool() = default;
    std::vector<std::unique_ptr<InferenceWorker>> m_workers;
};

} }
#endif
