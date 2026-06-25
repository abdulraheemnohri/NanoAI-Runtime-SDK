#include "model_cache.h"
#include <iostream>

namespace nanoai {
namespace memory {

ModelCache& ModelCache::getInstance() {
    static ModelCache instance;
    return instance;
}

void ModelCache::cacheWeights(const std::string& id, const std::string& data) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_cache[id] = data;
    std::cout << "ModelCache: Cached weights for [" << id << "] (" << data.size() << " bytes)." << std::endl;
}

std::string ModelCache::getWeights(const std::string& id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_cache.count(id)) return m_cache.at(id);
    return "";
}

bool ModelCache::hasWeights(const std::string& id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_cache.count(id) > 0;
}

void ModelCache::clear(const std::string& id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_cache.erase(id);
}

} // namespace memory
} // namespace nanoai
