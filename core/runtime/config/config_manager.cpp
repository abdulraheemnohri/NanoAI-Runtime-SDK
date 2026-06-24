#include "config_manager.h"

namespace nanoai {
namespace config {

ConfigManager& ConfigManager::getInstance() {
    static ConfigManager instance;
    return instance;
}

ConfigManager::ConfigManager() {
    m_configs["cluster.enabled"] = "true";
    m_configs["engine.workers"] = "4";
    m_configs["hal.auto_discovery"] = "true";
    m_configs["security.sandbox"] = "strict";
}

void ConfigManager::set(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_configs[key] = value;
}

std::string ConfigManager::get(const std::string& key, const std::string& defaultValue) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_configs.count(key)) return m_configs.at(key);
    return defaultValue;
}

int ConfigManager::getInt(const std::string& key, int defaultValue) {
    std::string val = get(key, "");
    if (val.empty()) return defaultValue;
    return std::stoi(val);
}

} // namespace config
} // namespace nanoai
