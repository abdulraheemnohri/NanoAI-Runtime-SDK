#ifndef NANOAI_MEMORY_MANAGER_H
#define NANOAI_MEMORY_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <chrono>

namespace nanoai {
namespace memory {

struct ModelMemoryInfo {
    std::string modelId;
    size_t sizeBytes;
    std::chrono::steady_clock::time_point lastUsed;
    bool pinned;
};

class MemoryManager {
public:
    static MemoryManager& getInstance();

    void registerModelUsage(const std::string& modelId, size_t sizeBytes);
    void pinModel(const std::string& modelId, bool pinned);
    std::vector<std::string> getUnloadCandidates(size_t requiredSpace);
    size_t getAvailableMemory() const;
    void setMemoryLimit(size_t limit);

private:
    MemoryManager();
    size_t m_memoryLimit;
    size_t m_currentUsage;
    std::map<std::string, ModelMemoryInfo> m_models;
    mutable std::mutex m_mutex;
};

} // namespace memory
} // namespace nanoai

#endif // NANOAI_MEMORY_MANAGER_H
