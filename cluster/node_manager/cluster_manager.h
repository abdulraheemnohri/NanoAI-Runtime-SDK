#ifndef NANOAI_CLUSTER_MANAGER_H
#define NANOAI_CLUSTER_MANAGER_H

#include <string>

namespace nanoai {
namespace cluster {

class ClusterManager {
public:
    static ClusterManager& getInstance();
    std::string getNodes();
    void sync();
};

} // namespace cluster
} // namespace nanoai

#endif // NANOAI_CLUSTER_MANAGER_H
