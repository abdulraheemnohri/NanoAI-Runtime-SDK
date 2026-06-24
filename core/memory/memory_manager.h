#ifndef NANOAI_MEMORY_MANAGER_H
#define NANOAI_MEMORY_MANAGER_H

#include <string>
#include <unordered_map>
#include <chrono>
#include <mutex>
#include <vector>

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
    bool shouldUnload(const std::string& modelId);
    std::vector<std::string> getUnloadCandidates(size_t requiredSpace);

    void setMemoryLimit(size_t limitBytes);
    size_t getAvailableMemory() const;

private:
    MemoryManager();
    std::unordered_map<std::string, ModelMemoryInfo> m_models;
    size_t m_memoryLimit;
    size_t m_currentUsage;
    mutable std::mutex m_mutex;
};

} // namespace memory
} // namespace nanoai

#endif // NANOAI_MEMORY_MANAGER_H
