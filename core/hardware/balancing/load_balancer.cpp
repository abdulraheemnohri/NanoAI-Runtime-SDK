#include "load_balancer.h"
#include <algorithm>

namespace nanoai {
namespace hardware {

LoadBalancer& LoadBalancer::getInstance() {
    static LoadBalancer instance;
    return instance;
}

std::shared_ptr<nanoai::hal::HardwareDevice> LoadBalancer::selectOptimalDevice(const std::vector<std::shared_ptr<nanoai::hal::HardwareDevice>>& devices) {
    if (devices.empty()) return nullptr;

    // Select device with lowest load
    return *std::min_element(devices.begin(), devices.end(), [](const auto& a, const auto& b) {
        return a->currentLoad() < b->currentLoad();
    });
}

} }
