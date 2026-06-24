#ifndef NANOAI_LOAD_BALANCER_H
#define NANOAI_LOAD_BALANCER_H

#include <string>
#include <vector>
#include "../discovery/hal.h"

namespace nanoai {
namespace hardware {

class LoadBalancer {
public:
    static LoadBalancer& getInstance();
    std::shared_ptr<hal::HardwareDevice> selectOptimalDevice(const std::vector<std::shared_ptr<hal::HardwareDevice>>& devices);
};

} }
#endif
