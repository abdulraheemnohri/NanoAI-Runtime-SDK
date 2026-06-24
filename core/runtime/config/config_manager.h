#ifndef NANOAI_CONFIG_MANAGER_H
#define NANOAI_CONFIG_MANAGER_H

#include <string>
#include <map>
#include <mutex>

namespace nanoai {
namespace config {

class ConfigManager {
public:
    static ConfigManager& getInstance();

    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key, const std::string& defaultValue = "");
    int getInt(const std::string& key, int defaultValue = 0);

private:
    ConfigManager();
    std::map<std::string, std::string> m_configs;
    std::mutex m_mutex;
};

} // namespace config
} // namespace nanoai

#endif // NANOAI_CONFIG_MANAGER_H
