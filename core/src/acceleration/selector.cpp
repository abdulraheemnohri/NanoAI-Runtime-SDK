#include "selector.h"
#include <algorithm>

namespace nanoai {

std::vector<DeviceCapability> SmartRuntimeSelector::getAvailableDevices() {
    std::vector<DeviceCapability> devices;

    // Default CPU
    devices.push_back({DeviceType::CPU, "Generic CPU", 1.0f, true});

    // Simulate GPU detection
    devices.push_back({DeviceType::GPU, "Integrated GPU (Vulkan)", 5.0f, true});

    // Simulate NPU detection
    devices.push_back({DeviceType::NPU, "Hardware NPU", 10.0f, false}); // Simulated as unavailable for now

    return devices;
}

DeviceType SmartRuntimeSelector::selectBestDevice() {
    auto devices = getAvailableDevices();

    // Sort by score descending
    std::sort(devices.begin(), devices.end(), [](const DeviceCapability& a, const DeviceCapability& b) {
        return a.score > b.score;
    });

    for (const auto& device : devices) {
        if (device.is_available) {
            return device.type;
        }
    }

    return DeviceType::CPU;
}

} // namespace nanoai
