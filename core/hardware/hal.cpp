#include "hal.h"
#include <iostream>
#include <sstream>

namespace nanoai {
namespace hal {

class SimulatedDevice : public HardwareDevice {
public:
    SimulatedDevice(DeviceCapability cap) : m_cap(cap) {}
    const DeviceCapability& getCapability() const override { return m_cap; }
    bool isAvailable() const override { return true; }
    float currentLoad() const override { return 0.15f; }
private:
    DeviceCapability m_cap;
};

HardwareAbstractionLayer& HardwareAbstractionLayer::getInstance() {
    static HardwareAbstractionLayer instance;
    return instance;
}

void HardwareAbstractionLayer::discoverHardware() {
    m_devices.clear();

    // CPU
    DeviceCapability cpu{"AMD Ryzen 9 7950X", DeviceCategory::CPU, "AMD", 65536, 48000, 16, 88.0f, true, true};
    m_devices.push_back(std::make_shared<SimulatedDevice>(cpu));

    // GPU
    DeviceCapability gpu{"NVIDIA RTX 5090", DeviceCategory::GPU, "NVIDIA", 32768, 30000, 16384, 99.5f, true, true};
    m_devices.push_back(std::make_shared<SimulatedDevice>(gpu));

    // NPU
    DeviceCapability npu{"Qualcomm Hexagon NPU", DeviceCategory::NPU, "Qualcomm", 0, 0, 1, 92.0f, true, true};
    m_devices.push_back(std::make_shared<SimulatedDevice>(npu));

    // Remote
    DeviceCapability remote{"Mac Studio Cluster Node", DeviceCategory::REMOTE, "Apple", 131072, 90000, 24, 95.0f, true, true};
    m_devices.push_back(std::make_shared<SimulatedDevice>(remote));

    std::cout << "HAL: Hardware discovery complete. Found " << m_devices.size() << " devices." << std::endl;
}

std::vector<std::shared_ptr<HardwareDevice>> HardwareAbstractionLayer::getAvailableDevices() {
    if (m_devices.empty()) discoverHardware();
    return m_devices;
}

std::string HardwareAbstractionLayer::generateCapabilityProfile() {
    if (m_devices.empty()) discoverHardware();
    std::stringstream ss;
    ss << "{\n  \"devices\": [";
    for(size_t i=0; i<m_devices.size(); ++i) {
        auto& c = m_devices[i]->getCapability();
        ss << "\n    {\"name\": \"" << c.name << "\", \"vendor\": \"" << c.vendor << "\", \"score\": " << c.performanceScore << "}";
        if(i < m_devices.size() - 1) ss << ",";
    }
    ss << "\n  ],\n  \"overall_score\": 98\n}";
    return ss.str();
}

std::shared_ptr<HardwareDevice> HardwareAbstractionLayer::getBestDeviceForTask(const std::string& taskType, size_t modelSize) {
    if (m_devices.empty()) discoverHardware();
    // Simple priority: NPU -> GPU -> REMOTE -> CPU
    for(auto& d : m_devices) if(d->getCapability().category == DeviceCategory::NPU) return d;
    for(auto& d : m_devices) if(d->getCapability().category == DeviceCategory::GPU) return d;
    return m_devices[0];
}

} // namespace hal
} // namespace nanoai
