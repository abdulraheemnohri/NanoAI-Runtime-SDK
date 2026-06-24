#include "cluster_manager.h"
namespace nanoai { namespace cluster {
ClusterManager& ClusterManager::getInstance() { static ClusterManager instance; return instance; }
std::string ClusterManager::getNodes() { return "[{\"id\": \"remote_01\", \"type\": \"server\"}]"; }
} }
