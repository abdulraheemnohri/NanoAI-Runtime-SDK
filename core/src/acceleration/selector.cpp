#include "selector.h"
#include "../networking/network_manager.h"
#include <algorithm>
#include <iostream>
#include <mutex>
#include <unordered_map>

namespace nanoai {

static std::mutex g_resource_mutex;
static std::unordered_map<DeviceType, int> g_active_loads;

std::vector<DeviceCapability> SmartRuntimeSelector::getAvailableDevices() {
    std::vector<DeviceCapability> devices;

    // Local Hardware
    devices.push_back({DeviceType::CPU, "Local CPU", 1.0f, true});
    devices.push_back({DeviceType::GPU, "Local GPU (Vulkan/Metal)", 5.0f, true});
    devices.push_back({DeviceType::NPU, "Local NPU (Hexagon/APU/TPU)", 10.0f, true});

    // Roadmap v4: Include remote distributed nodes as providers
    auto peers = NetworkManager::discoverPeers();
    for (const auto& peer : peers) {
        if (peer.is_online) {
            // Score based on peer compute power
            devices.push_back({DeviceType::NPU, "Remote Node [" + peer.id + "]", peer.available_compute_power * 10.0f, true});
        }
    }

    return devices;
}

DeviceType SmartRuntimeSelector::selectBestDevice() {
    std::lock_guard<std::mutex> lock(g_resource_mutex);
    auto devices = getAvailableDevices();

    std::sort(devices.begin(), devices.end(), [](const DeviceCapability& a, const DeviceCapability& b) {
        float score_a = a.score - (g_active_loads[a.type] * 2.0f);
        float score_b = b.score - (g_active_loads[b.type] * 2.0f);
        return score_a > score_b;
    });

    for (const auto& device : devices) {
        if (device.is_available) {
            g_active_loads[device.type]++;
            std::cout << "Smart Selector: Distributing to provider: " << device.name << std::endl;
            return device.type;
        }
    }

    return DeviceType::CPU;
}

} // namespace nanoai
