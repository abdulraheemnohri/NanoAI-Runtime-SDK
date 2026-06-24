#ifndef NANOAI_DISPATCHER_H
#define NANOAI_DISPATCHER_H

#include <string>
#include <vector>
#include "../workers/inference_worker.h"

namespace nanoai {
namespace engine {

class Dispatcher {
public:
    static Dispatcher& getInstance();
    void dispatch(const InferenceTask& task);
};

} // namespace engine
} // namespace nanoai

#endif // NANOAI_DISPATCHER_H
