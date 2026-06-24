#ifndef NANOAI_PERMISSION_MANAGER_H
#define NANOAI_PERMISSION_MANAGER_H
#include <string>
#include <vector>
namespace nanoai { namespace security {
class PermissionManager {
public:
    static bool checkPermission(const std::string& app, const std::string& resource);
};
} }
#endif
