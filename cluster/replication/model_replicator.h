#ifndef NANOAI_MODEL_REPLICATOR_H
#define NANOAI_MODEL_REPLICATOR_H

#include <string>

namespace nanoai {
namespace cluster {

class ModelReplicator {
public:
    static ModelReplicator& getInstance();

    void replicate(const std::string& modelId, const std::string& targetNode);
    void verifyReplica(const std::string& modelId, const std::string& nodeId);
};

} // namespace cluster
} // namespace nanoai

#endif // NANOAI_MODEL_REPLICATOR_H
