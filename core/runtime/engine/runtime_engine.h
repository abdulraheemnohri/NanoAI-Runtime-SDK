#ifndef NANOAI_RUNTIME_ENGINE_H
#define NANOAI_RUNTIME_ENGINE_H

#include <vector>
#include <memory>
#include "../workers/inference_worker.h"

namespace nanoai {
namespace engine {

class RuntimeEngine {
public:
    static RuntimeEngine& getInstance();
    void initialize(int workerCount);
    void shutdown();
    void submitTask(const InferenceTask& task);

private:
    RuntimeEngine() = default;
    std::vector<std::unique_ptr<InferenceWorker>> m_workers;
};

} // namespace engine
} // namespace nanoai

#endif // NANOAI_RUNTIME_ENGINE_H
