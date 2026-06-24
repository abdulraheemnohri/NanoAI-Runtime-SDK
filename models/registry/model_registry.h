#ifndef NANOAI_MODEL_REGISTRY_H
#define NANOAI_MODEL_REGISTRY_H

#include <string>
#include <map>
#include <mutex>

namespace nanoai {
namespace models {

class ModelRegistry {
public:
    static ModelRegistry& getInstance();

    void registerModel(const std::string& id, const std::string& path);
    std::string getModelPath(const std::string& id);
    bool hasModel(const std::string& id);
    void unregisterModel(const std::string& id);

private:
    ModelRegistry() = default;
    std::map<std::string, std::string> m_models;
    std::mutex m_mutex;
};

} // namespace models
} // namespace nanoai

#endif // NANOAI_MODEL_REGISTRY_H
