#ifndef NANOAI_INTEGRITY_CHECKER_H
#define NANOAI_INTEGRITY_CHECKER_H

#include <string>

namespace nanoai {
namespace security {

class IntegrityChecker {
public:
    static bool verifyModel(const std::string& modelPath);
    static std::string calculateHash(const std::string& path);
};

} // namespace security
} // namespace nanoai

#endif // NANOAI_INTEGRITY_CHECKER_H
