#include "model_registry.h"

namespace nanoai {
namespace models {

ModelRegistry& ModelRegistry::getInstance() {
    static ModelRegistry instance;
    return instance;
}

void ModelRegistry::registerModel(const std::string& id, const std::string& path) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_models[id] = path;
}

std::string ModelRegistry::getModelPath(const std::string& id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_models.count(id)) {
        return m_models.at(id);
    }
    return "";
}

bool ModelRegistry::hasModel(const std::string& id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_models.count(id) > 0;
}

void ModelRegistry::unregisterModel(const std::string& id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_models.erase(id);
}

} // namespace models
} // namespace nanoai
