#ifndef NANOAI_MODEL_CACHE_H
#define NANOAI_MODEL_CACHE_H
#include <string>
#include <map>
namespace nanoai { namespace memory {
class ModelCache {
public:
    static ModelCache& getInstance();
    void cacheWeights(const std::string& id, const std::string& data);
    std::string getWeights(const std::string& id);
private:
    std::map<std::string, std::string> m_cache;
};
} }
#endif
