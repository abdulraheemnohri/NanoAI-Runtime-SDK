#include "selector.h"
#include <algorithm>
#include <iostream>
#include <mutex>
#include <unordered_map>

namespace nanoai {

// Simulate hardware resource tracking
static std::mutex g_resource_mutex;
static std::unordered_map<DeviceType, int> g_active_loads;

std::vector<DeviceCapability> SmartRuntimeSelector::getAvailableDevices() {
    std::vector<DeviceCapability> devices;
    devices.push_back({DeviceType::CPU, "Generic CPU", 1.0f, true});
    devices.push_back({DeviceType::GPU, "Integrated GPU (Vulkan/Metal)", 5.0f, true});
    devices.push_back({DeviceType::NPU, "Dedicated NPU (Hexagon/APU/TPU)", 10.0f, true});
    return devices;
}

DeviceType SmartRuntimeSelector::selectBestDevice() {
    std::lock_guard<std::mutex> lock(g_resource_mutex);
    auto devices = getAvailableDevices();

    // Prioritize NPU > GPU > CPU, but consider load balancing for multi-model parallel execution
    std::sort(devices.begin(), devices.end(), [](const DeviceCapability& a, const DeviceCapability& b) {
        // Simple heuristic: adjust score based on active load to distribute models
        float score_a = a.score - (g_active_loads[a.type] * 2.0f);
        float score_b = b.score - (g_active_loads[b.type] * 2.0f);
        return score_a > score_b;
    });

    for (const auto& device : devices) {
        if (device.is_available) {
            g_active_loads[device.type]++;
            std::cout << "Smart Selector: Distributing model to " << device.name
                      << " (Current Active Models on device: " << g_active_loads[device.type] << ")" << std::endl;
            return device.type;
        }
    }

    return DeviceType::CPU;
}

} // namespace nanoai
