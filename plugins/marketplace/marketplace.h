#ifndef NANOAI_PLUGIN_MARKETPLACE_H
#define NANOAI_PLUGIN_MARKETPLACE_H

#include <string>
#include <vector>

namespace nanoai {
namespace plugins {

struct PluginEntry {
    std::string id;
    std::string name;
    std::string version;
    std::string category;
};

class PluginMarketplace {
public:
    static PluginMarketplace& getInstance();

    std::vector<PluginEntry> listAvailablePlugins();
    bool downloadPlugin(const std::string& pluginId);
    void installPlugin(const std::string& pluginId);

private:
    PluginMarketplace() = default;
};

} // namespace plugins
} // namespace nanoai

#endif // NANOAI_PLUGIN_MARKETPLACE_H
