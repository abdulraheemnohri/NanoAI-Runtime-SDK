#ifndef NANOAI_INFERENCE_WORKER_H
#define NANOAI_INFERENCE_WORKER_H

#include <string>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "nanoai/runtime.h"

namespace nanoai {
namespace engine {

struct InferenceTask {
    std::string taskId;
    std::string modelId;
    std::string input;
    int priority;
};

class InferenceWorker {
public:
    InferenceWorker(int id);
    ~InferenceWorker();

    void start();
    void stop();
    void addTask(const InferenceTask& task);

private:
    void workLoop();

    int m_id;
    std::atomic<bool> m_running;
    std::thread m_thread;
    std::queue<InferenceTask> m_tasks;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};

} // namespace engine
} // namespace nanoai

#endif // NANOAI_INFERENCE_WORKER_H
