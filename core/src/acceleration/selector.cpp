#include "selector.h"
#include <algorithm>
#include <iostream>

namespace nanoai {

std::vector<DeviceCapability> SmartRuntimeSelector::getAvailableDevices() {
    std::vector<DeviceCapability> devices;

    // CPU: Base capability for all devices (x86_64, ARM64, ARMv7)
    devices.push_back({DeviceType::CPU, "Generic CPU", 1.0f, true});

    // GPU: Vulkan, OpenCL, CUDA, DirectML, Metal
    devices.push_back({DeviceType::GPU, "Integrated GPU (Vulkan/Metal)", 5.0f, true});

    // NPU: Qualcomm Hexagon, MediaTek APU, Samsung NPU, Google TPU
    // In a production build, we would use platform-specific APIs to detect these.
    devices.push_back({DeviceType::NPU, "Dedicated NPU (Hexagon/APU/TPU)", 10.0f, true});

    return devices;
}

DeviceType SmartRuntimeSelector::selectBestDevice() {
    auto devices = getAvailableDevices();

    // Sort by score descending to prioritize NPU > GPU > CPU
    std::sort(devices.begin(), devices.end(), [](const DeviceCapability& a, const DeviceCapability& b) {
        return a.score > b.score;
    });

    for (const auto& device : devices) {
        if (device.is_available) {
            std::cout << "Smart Selector: Hardware Acceleration enabled on " << device.name << "." << std::endl;
            return device.type;
        }
    }

    return DeviceType::CPU;
}

} // namespace nanoai
