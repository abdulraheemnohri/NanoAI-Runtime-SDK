#ifndef NANOAI_PERMISSION_MANAGER_H
#define NANOAI_PERMISSION_MANAGER_H

#include <string>
#include <vector>
#include <mutex>
#include <set>

namespace nanoai {
namespace security {

class PermissionManager {
public:
    static PermissionManager& getInstance();

    bool checkPermission(const std::string& app, const std::string& resource);
    void grantPermission(const std::string& app, const std::string& resource);
    void revokePermission(const std::string& app, const std::string& resource);

private:
    PermissionManager() = default;
    std::set<std::pair<std::string, std::string>> m_permissions;
    std::mutex m_mutex;
};

} // namespace security
} // namespace nanoai

#endif // NANOAI_PERMISSION_MANAGER_H
