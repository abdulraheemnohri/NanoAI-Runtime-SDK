#include "dispatcher.h"
#include "../engine/runtime_engine.h"
#include <iostream>

namespace nanoai {
namespace engine {

Dispatcher& Dispatcher::getInstance() {
    static Dispatcher instance;
    return instance;
}

void Dispatcher::dispatch(const InferenceTask& task) {
    std::cout << "Dispatcher: Routing task " << task.taskId << " to optimal engine worker..." << std::endl;
    RuntimeEngine::getInstance().submitTask(task);
}

} // namespace engine
} // namespace nanoai
