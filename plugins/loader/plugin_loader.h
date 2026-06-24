#ifndef NANOAI_PLUGIN_LOADER_H
#define NANOAI_PLUGIN_LOADER_H
#include <string>
namespace nanoai { namespace plugins {
class PluginLoader {
public:
    static void* loadLibrary(const std::string& path) { return nullptr; }
};
} }
#endif
