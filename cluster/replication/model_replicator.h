#ifndef NANOAI_MODEL_REPLICATOR_H
#define NANOAI_MODEL_REPLICATOR_H
#include <string>
namespace nanoai { namespace cluster {
class ModelReplicator {
public:
    static void replicate(const std::string& modelId, const std::string& targetNode);
};
} }
#endif
