#include "model_registry.h"
namespace nanoai { namespace models {
ModelRegistry& ModelRegistry::getInstance() { static ModelRegistry instance; return instance; }
void ModelRegistry::registerModel(const std::string& id, const std::string& path) {}
} }
