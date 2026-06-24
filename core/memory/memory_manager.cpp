#include "memory_manager.h"
#include <algorithm>
#include <iostream>

namespace nanoai {
namespace memory {

MemoryManager& MemoryManager::getInstance() {
    static MemoryManager instance;
    return instance;
}

MemoryManager::MemoryManager() : m_memoryLimit(8192ULL * 1024 * 1024), m_currentUsage(0) {}

void MemoryManager::registerModelUsage(const std::string& modelId, size_t sizeBytes) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_models.find(modelId);
    if (it != m_models.end()) {
        it->second.lastUsed = std::chrono::steady_clock::now();
    } else {
        m_models[modelId] = {modelId, sizeBytes, std::chrono::steady_clock::now(), false};
        m_currentUsage += sizeBytes;
    }
    std::cout << "MemoryManager: Model " << modelId << " usage updated. Total usage: " << (m_currentUsage / (1024*1024)) << " MB" << std::endl;
}

void MemoryManager::pinModel(const std::string& modelId, bool pinned) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_models.count(modelId)) m_models[modelId].pinned = pinned;
}

std::vector<std::string> MemoryManager::getUnloadCandidates(size_t requiredSpace) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<ModelMemoryInfo*> candidates;
    for (auto& pair : m_models) {
        if (!pair.second.pinned) candidates.push_back(&pair.second);
    }

    // Sort by last used (LRU)
    std::sort(candidates.begin(), candidates.end(), [](const auto* a, const auto* b) {
        return a->lastUsed < b->lastUsed;
    });

    std::vector<std::string> toUnload;
    size_t freed = 0;
    for (auto* c : candidates) {
        if (freed >= requiredSpace) break;
        toUnload.push_back(c->modelId);
        freed += c->sizeBytes;
    }
    return toUnload;
}

size_t MemoryManager::getAvailableMemory() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_memoryLimit > m_currentUsage ? m_memoryLimit - m_currentUsage : 0;
}

void MemoryManager::setMemoryLimit(size_t limit) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_memoryLimit = limit;
}

} // namespace memory
} // namespace nanoai
