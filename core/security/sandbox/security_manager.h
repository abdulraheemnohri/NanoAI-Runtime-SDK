#ifndef NANOAI_SECURITY_MANAGER_H
#define NANOAI_SECURITY_MANAGER_H

#include <string>
#include <vector>

namespace nanoai {
namespace security {

class SecurityManager {
public:
    static SecurityManager& getInstance();
    bool validateAccess(const std::string& modelId, const std::string& resource);
    void enforceSandbox(const std::string& modelId);
};

} // namespace security
} // namespace nanoai

#endif // NANOAI_SECURITY_MANAGER_H
