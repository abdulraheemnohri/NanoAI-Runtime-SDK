#ifndef NANOAI_MODEL_CACHE_H
#define NANOAI_MODEL_CACHE_H

#include <string>
#include <map>
#include <mutex>

namespace nanoai {
namespace memory {

class ModelCache {
public:
    static ModelCache& getInstance();

    void cacheWeights(const std::string& id, const std::string& data);
    std::string getWeights(const std::string& id);
    bool hasWeights(const std::string& id);
    void clear(const std::string& id);

private:
    ModelCache() = default;
    std::map<std::string, std::string> m_cache;
    std::mutex m_mutex;
};

} // namespace memory
} // namespace nanoai

#endif // NANOAI_MODEL_CACHE_H
