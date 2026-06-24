#include "hal.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "../../../backends/nvidia/cuda/cuda_backend.h"
#include "../../../backends/apple/metal/metal_backend.h"
#include "../../../backends/qualcomm/hexagon/hexagon_backend.h"

#ifdef __linux__
#include <unistd.h>
#endif

namespace nanoai {
namespace hal {

class SimulatedDevice : public HardwareDevice {
public:
    SimulatedDevice(DeviceCapability cap) : m_cap(cap) {}
    const DeviceCapability& getCapability() const override { return m_cap; }
    bool isAvailable() const override { return true; }
    float currentLoad() const override { return 0.05f + (static_cast<float>(rand() % 20) / 100.0f); }
private:
    DeviceCapability m_cap;
};

HardwareAbstractionLayer& HardwareAbstractionLayer::getInstance() {
    static HardwareAbstractionLayer instance;
    return instance;
}

static bool checkCPUInfo(const std::string& pattern) {
    std::ifstream file("/proc/cpuinfo");
    if (!file.is_open()) return false;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(pattern) != std::string::npos) return true;
    }
    return false;
}

void HardwareAbstractionLayer::discoverHardware() {
    m_devices.clear();

    std::cout << "HAL: Starting universal hardware discovery (NRX)..." << std::endl;

    // 1. CPU Detection
#ifdef __linux__
    if (checkCPUInfo("Intel")) {
        m_devices.push_back(std::make_shared<SimulatedDevice>(
            DeviceCapability{"Intel Core Processor", DeviceCategory::CPU, "Intel", 32768, 32000, 16, 85.0f, true, true}
        ));
    } else if (checkCPUInfo("AMD")) {
        m_devices.push_back(std::make_shared<SimulatedDevice>(
            DeviceCapability{"AMD Ryzen Processor", DeviceCategory::CPU, "AMD", 32768, 32000, 16, 86.0f, true, true}
        ));
    } else {
        m_devices.push_back(std::make_shared<SimulatedDevice>(
            DeviceCapability{"Generic ARM/x86 CPU", DeviceCategory::CPU, "Generic", 16384, 16000, 8, 70.0f, true, true}
        ));
    }
#else
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Host CPU", DeviceCategory::CPU, "Generic", 16384, 16000, 8, 75.0f, true, true}
    ));
#endif

    // 2. GPU/NPU Backend Discovery
    if (backends::CudaBackend::isAvailable()) {
        backends::CudaBackend b; b.initialize();
        m_devices.push_back(std::make_shared<SimulatedDevice>(
            DeviceCapability{b.getDeviceInfo(), DeviceCategory::GPU, "NVIDIA", 12288, 12000, 5888, 98.0f, true, true}
        ));
    }

    if (backends::MetalBackend::isAvailable()) {
        backends::MetalBackend b; b.initialize();
        m_devices.push_back(std::make_shared<SimulatedDevice>(
            DeviceCapability{b.getDeviceInfo(), DeviceCategory::GPU, "Apple", 65536, 64000, 40, 92.0f, true, true}
        ));
    }

    if (backends::HexagonBackend::isAvailable()) {
        backends::HexagonBackend b; b.initialize();
        m_devices.push_back(std::make_shared<SimulatedDevice>(
            DeviceCapability{b.getDeviceInfo(), DeviceCategory::NPU, "Qualcomm", 0, 0, 1, 95.0f, true, true}
        ));
    }

    // Always include a generic NPU for simulation in this version
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Integrated AI NPU", DeviceCategory::NPU, "Generic", 0, 0, 1, 90.0f, true, true}
    ));

    std::cout << "HAL: Discovery complete. Found " << m_devices.size() << " NRX platforms." << std::endl;
}

std::vector<std::shared_ptr<HardwareDevice>> HardwareAbstractionLayer::getAvailableDevices() {
    if (m_devices.empty()) discoverHardware();
    return m_devices;
}

std::string HardwareAbstractionLayer::generateCapabilityProfile() {
    if (m_devices.empty()) discoverHardware();

    std::stringstream ss;
    ss << "{\n";
    ss << "  \"devices\": [\n";
    for (size_t i = 0; i < m_devices.size(); ++i) {
        const auto& cap = m_devices[i]->getCapability();
        ss << "    {\"name\": \"" << cap.name << "\", \"vendor\": \"" << cap.vendor << "\", \"score\": " << cap.performanceScore << "}";
        if (i < m_devices.size() - 1) ss << ",";
        ss << "\n";
    }
    ss << "  ],\n";
    ss << "  \"total_platforms\": " << m_devices.size() << "\n";
    ss << "}";
    return ss.str();
}

std::shared_ptr<HardwareDevice> HardwareAbstractionLayer::getBestDeviceForTask(const std::string& taskType, size_t modelSize) {
    if (m_devices.empty()) discoverHardware();

    // Prefer GPU for Vision/LLM if available
    for (auto& d : m_devices) {
        if (d->getCapability().category == DeviceCategory::GPU) return d;
    }

    // Fallback to NPU
    for (auto& d : m_devices) {
        if (d->getCapability().category == DeviceCategory::NPU) return d;
    }

    return m_devices[0]; // CPU fallback
}

} // namespace hal
} // namespace nanoai
