#ifndef NANOAI_LOAD_MIGRATOR_H
#define NANOAI_LOAD_MIGRATOR_H

#include <string>
#include <vector>

namespace nanoai {
namespace cluster {

class LoadMigrator {
public:
    static LoadMigrator& getInstance();
    bool migrateSession(const std::string& sessionId, const std::string& targetNodeId);
    void balanceClusterLoad();
};

} // namespace cluster
} // namespace nanoai

#endif // NANOAI_LOAD_MIGRATOR_H
