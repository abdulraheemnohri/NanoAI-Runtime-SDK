#ifndef NANOAI_MODEL_LOADER_H
#define NANOAI_MODEL_LOADER_H
#include <string>
namespace nanoai { namespace models {
class ModelLoader {
public:
    static bool load(const std::string& path) { return true; }
};
} }
#endif
