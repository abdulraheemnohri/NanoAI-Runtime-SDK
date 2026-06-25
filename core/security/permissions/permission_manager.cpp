#include "permission_manager.h"
#include <iostream>

namespace nanoai {
namespace security {

PermissionManager& PermissionManager::getInstance() {
    static PermissionManager instance;
    return instance;
}

bool PermissionManager::checkPermission(const std::string& app, const std::string& resource) {
    std::lock_guard<std::mutex> lock(m_mutex);
    bool allowed = m_permissions.count({app, resource}) > 0;
    std::cout << "Permission: App [" << app << "] access to [" << resource << "] -> " << (allowed ? "ALLOWED" : "DENIED") << std::endl;
    return allowed;
}

void PermissionManager::grantPermission(const std::string& app, const std::string& resource) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_permissions.insert({app, resource});
}

void PermissionManager::revokePermission(const std::string& app, const std::string& resource) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_permissions.erase({app, resource});
}

} // namespace security
} // namespace nanoai
