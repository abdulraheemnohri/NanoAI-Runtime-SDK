#include "hal.h"
#include <iostream>
#include <algorithm>
#include <sstream>

namespace nanoai {
namespace hal {

class SimulatedDevice : public HardwareDevice {
public:
    SimulatedDevice(DeviceCapability cap) : m_cap(cap) {}
    const DeviceCapability& getCapability() const override { return m_cap; }
    bool isAvailable() const override { return true; }
    float currentLoad() const override { return 0.05f + (rand() % 20) / 100.0f; }
private:
    DeviceCapability m_cap;
};

HardwareAbstractionLayer& HardwareAbstractionLayer::getInstance() {
    static HardwareAbstractionLayer instance;
    return instance;
}

void HardwareAbstractionLayer::discoverHardware() {
    m_devices.clear();

    // CPU: Desktop/Server/Mobile
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Intel Core i9-14900K", DeviceCategory::CPU, "Intel", 65536, 48000, 24, 88.0f, true, true}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"AMD Ryzen 9 7950X", DeviceCategory::CPU, "AMD", 65536, 48000, 16, 89.0f, true, true}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Apple M3 Max", DeviceCategory::CPU, "Apple", 131072, 90000, 16, 92.0f, true, true}
    ));

    // GPU: NVIDIA/AMD/Intel/Apple/Mobile
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"NVIDIA RTX 5090", DeviceCategory::GPU, "NVIDIA", 32768, 30000, 16384, 99.8f, true, true}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"AMD Radeon Pro W7900", DeviceCategory::GPU, "AMD", 49152, 45000, 6144, 94.0f, true, true}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Apple M3 GPU", DeviceCategory::GPU, "Apple", 0, 0, 40, 91.0f, true, true}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Qualcomm Adreno 750", DeviceCategory::GPU, "Qualcomm", 0, 0, 1, 78.0f, true, true}
    ));

    // NPU: Qualcomm/MediaTek/Samsung/Google
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Qualcomm Hexagon NPU", DeviceCategory::NPU, "Qualcomm", 0, 0, 1, 95.0f, true, true}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"MediaTek APU 790", DeviceCategory::NPU, "MediaTek", 0, 0, 1, 88.0f, true, true}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Samsung NPU (Exynos)", DeviceCategory::NPU, "Samsung", 0, 0, 1, 85.0f, true, true}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Google Tensor TPU", DeviceCategory::NPU, "Google", 0, 0, 1, 90.0f, true, true}
    ));

    // AI Accelerators: Coral/Groq/Hailo
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Google Coral Edge TPU", DeviceCategory::ACCELERATOR, "Google", 8, 8, 1, 82.0f, true, false}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Groq LPU Node", DeviceCategory::ACCELERATOR, "Groq", 256, 256, 1, 99.0f, true, true}
    ));
    m_devices.push_back(std::make_shared<SimulatedDevice>(
        DeviceCapability{"Hailo-8 AI Processor", DeviceCategory::ACCELERATOR, "Hailo", 4, 4, 1, 85.0f, true, false}
    ));

    std::cout << "HAL: Global Hardware Discovery complete. Total platforms: " << m_devices.size() << std::endl;
}

std::vector<std::shared_ptr<HardwareDevice>> HardwareAbstractionLayer::getAvailableDevices() {
    if (m_devices.empty()) discoverHardware();
    return m_devices;
}

std::string HardwareAbstractionLayer::generateCapabilityProfile() {
    if (m_devices.empty()) discoverHardware();
    std::stringstream ss;
    ss << "{\n";
    ss << "  \"cpu\": \"Apple M3 Max\",\n";
    ss << "  \"gpu\": \"RTX 5090\",\n";
    ss << "  \"npu\": \"Hexagon NPU\",\n";
    ss << "  \"ram\": \"128GB\",\n";
    ss << "  \"vram\": \"32GB\",\n";
    ss << "  \"score\": 98,\n";
    ss << "  \"discovered_devices\": " << m_devices.size() << "\n";
    ss << "}";
    return ss.str();
}

std::shared_ptr<HardwareDevice> HardwareAbstractionLayer::getBestDeviceForTask(const std::string& taskType, size_t modelSize) {
    if (m_devices.empty()) discoverHardware();

    // Preference Logic
    if (taskType == "LLM_FAST") {
        for(auto& d : m_devices) if(d->getCapability().vendor == "Qualcomm" && d->getCapability().category == DeviceCategory::NPU) return d;
    }
    if (taskType == "VISION") {
        for(auto& d : m_devices) if(d->getCapability().vendor == "NVIDIA" && d->getCapability().category == DeviceCategory::GPU) return d;
    }
    if (taskType == "TRANSCRIPTION") {
        for(auto& d : m_devices) if(d->getCapability().category == DeviceCategory::GPU) return d;
    }

    return m_devices[0]; // CPU fallback
}

} // namespace hal
} // namespace nanoai
