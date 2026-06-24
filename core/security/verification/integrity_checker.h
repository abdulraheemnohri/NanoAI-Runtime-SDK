#ifndef NANOAI_INTEGRITY_CHECKER_H
#define NANOAI_INTEGRITY_CHECKER_H
#include <string>
namespace nanoai { namespace security {
class IntegrityChecker {
public:
    static bool verifyModel(const std::string& path);
};
} }
#endif
