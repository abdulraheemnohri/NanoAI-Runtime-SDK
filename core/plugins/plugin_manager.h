#ifndef NANOAI_PLUGIN_MANAGER_H
#define NANOAI_PLUGIN_MANAGER_H
#include <string>
namespace nanoai { namespace plugins {
class PluginManager {
public:
    static PluginManager& getInstance();
    void loadPlugins(const std::string& dir);
};
} }
#endif
