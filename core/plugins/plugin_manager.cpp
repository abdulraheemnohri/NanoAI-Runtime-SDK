#include "plugin_manager.h"
#include <iostream>
namespace nanoai { namespace plugins {
PluginManager& PluginManager::getInstance() { static PluginManager instance; return instance; }
void PluginManager::loadPlugins(const std::string& dir) { std::cout << "PluginManager: Scanning " << dir << std::endl; }
} }
