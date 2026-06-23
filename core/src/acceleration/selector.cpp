#include "selector.h"
#include <algorithm>
#include <iostream>

namespace nanoai {

std::vector<DeviceCapability> SmartRuntimeSelector::getAvailableDevices() {
    std::vector<DeviceCapability> devices;

    // Default CPU
    devices.push_back({DeviceType::CPU, "Generic CPU", 1.0f, true});

    // Simulate GPU detection based on platform/drivers
    // In a real implementation, we would check for Vulkan/OpenCL/Metal support.
    devices.push_back({DeviceType::GPU, "Integrated GPU (Vulkan/OpenCL)", 5.0f, true});

    // Simulate NPU detection
    devices.push_back({DeviceType::NPU, "Hardware NPU (Hexagon/APU)", 10.0f, false});

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
            std::cout << "Smart Selector: Selected " << device.name << " as the optimal device." << std::endl;
            return device.type;
        }
    }

    return DeviceType::CPU;
}

} // namespace nanoai
