#ifndef NANOAI_MODEL_REGISTRY_H
#define NANOAI_MODEL_REGISTRY_H
#include <string>
#include <map>
namespace nanoai { namespace models {
class ModelRegistry {
public:
    static ModelRegistry& getInstance();
    void registerModel(const std::string& id, const std::string& path);
};
} }
#endif
