#ifndef NANOAI_OS_LAYER_H
#define NANOAI_OS_LAYER_H

#include <string>
#include <vector>

namespace nanoai {
namespace os {

class AiOSKernel {
public:
    static AiOSKernel& getInstance();
    void boot();
    void shutdown();

    // Low-level resource management
    void allocateNPU(const std::string& processId);
    void releaseNPU(const std::string& processId);

    // System-wide orchestration
    std::string dispatchGlobalTask(const std::string& task);
};

} // namespace os
} // namespace nanoai

#endif // NANOAI_OS_LAYER_H
