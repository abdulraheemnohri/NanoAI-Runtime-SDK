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

    // Local Hardware Detection Simulation
    devices.push_back({DeviceType::CPU, "Local CPU (x86_64/ARM)", 1.0f, true});

    // GPU Detection
    devices.push_back({DeviceType::GPU, "NVIDIA GPU (CUDA)", 7.0f, true}); // Score based on CUDA availability
    devices.push_back({DeviceType::GPU, "Integrated GPU (Vulkan/Metal)", 5.0f, true});

    // NPU Detection: Qualcomm Hexagon, MediaTek APU, Samsung NPU, Google TPU
    devices.push_back({DeviceType::NPU, "Qualcomm Hexagon NPU", 10.0f, true});
    devices.push_back({DeviceType::NPU, "MediaTek APU", 10.0f, false});
    devices.push_back({DeviceType::NPU, "Samsung NPU", 10.0f, false});
    devices.push_back({DeviceType::NPU, "Google TPU", 12.0f, false});

    // Distributed nodes
    auto peers = NetworkManager::discoverPeers();
    for (const auto& peer : peers) {
        if (peer.is_online) {
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
            std::cout << "Smart Selector: Optimal device detected: " << device.name << std::endl;
            return device.type;
        }
    }

    return DeviceType::CPU;
}

} // namespace nanoai
