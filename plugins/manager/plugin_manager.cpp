#include "plugin_manager.h"
#include <iostream>
#include <vector>

#ifdef __linux__
#include <dlfcn.h>
#endif

namespace nanoai {
namespace plugins {

PluginManager& PluginManager::getInstance() {
    static PluginManager instance;
    return instance;
}

void PluginManager::loadPlugins(const std::string& dir) {
    std::cout << "PluginManager: Scanning " << dir << " for .so/.dll plugins..." << std::endl;

    // In a real system, we would iterate over files in 'dir'
    // For now, we simulate loading a specific plugin if it existed
    std::string simulatedPlugin = dir + "libcoding_plugin.so";

#ifdef __linux__
    void* handle = dlopen(simulatedPlugin.c_str(), RTLD_LAZY);
    if (!handle) {
        // Expected since the file doesn't actually exist in this sandbox yet
        std::cout << "PluginManager: [Info] No external plugins found in " << dir << " (using built-ins)." << std::endl;
    } else {
        std::cout << "PluginManager: Loaded " << simulatedPlugin << " successfully." << std::endl;
        // Logic to extract entry points would go here
        m_handles.push_back(handle);
    }
#else
    std::cout << "PluginManager: Plugin loading only supported on Linux/POSIX in this version." << std::endl;
#endif
}

PluginManager::~PluginManager() {
#ifdef __linux__
    for (void* h : m_handles) {
        if (h) dlclose(h);
    }
#endif
}

} // namespace plugins
} // namespace nanoai
