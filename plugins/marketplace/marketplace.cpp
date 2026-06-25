#include "marketplace.h"
#include <iostream>

namespace nanoai {
namespace plugins {

PluginMarketplace& PluginMarketplace::getInstance() {
    static PluginMarketplace instance;
    return instance;
}

std::vector<PluginEntry> PluginMarketplace::listAvailablePlugins() {
    return {
        {"P1", "AdvancedVision_Pro", "2.1.0", "Vision"},
        {"P2", "MedicalDiag_AI", "1.0.5", "Medical"},
        {"P3", "CodeRefactor_v3", "3.0.0", "Coding"}
    };
}

bool PluginMarketplace::downloadPlugin(const std::string& id) {
    std::cout << "Marketplace: Downloading plugin [" << id << "] from NRX cloud..." << std::endl;
    return true;
}

void PluginMarketplace::installPlugin(const std::string& id) {
    std::cout << "Marketplace: Installing [" << id << "] into local runtime environment." << std::endl;
}

} // namespace plugins
} // namespace nanoai
