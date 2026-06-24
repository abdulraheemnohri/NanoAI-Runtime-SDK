#ifndef NANOAI_PLUGIN_MANAGER_H
#define NANOAI_PLUGIN_MANAGER_H

#include <string>
#include <vector>

namespace nanoai {
namespace plugins {

class PluginManager {
public:
    static PluginManager& getInstance();
    void loadPlugins(const std::string& dir);

    ~PluginManager();

private:
    PluginManager() = default;
    std::vector<void*> m_handles;
};

} // namespace plugins
} // namespace nanoai

#endif // NANOAI_PLUGIN_MANAGER_H
