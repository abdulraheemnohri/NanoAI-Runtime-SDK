#ifndef NANOAI_HAL_H
#define NANOAI_HAL_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace nanoai {
namespace hal {

enum class DeviceCategory { CPU, GPU, NPU, TPU, DSP, ACCELERATOR, REMOTE };

struct DeviceCapability {
    std::string name;
    DeviceCategory category;
    std::string vendor;
    size_t totalMemory;
    size_t availableMemory;
    int coreCount;
    float performanceScore;
    bool supportsInt8;
    bool supportsFP16;
};

class HardwareDevice {
public:
    virtual ~HardwareDevice() = default;
    virtual const DeviceCapability& getCapability() const = 0;
    virtual bool isAvailable() const = 0;
    virtual float currentLoad() const = 0;
};

class HardwareAbstractionLayer {
public:
    static HardwareAbstractionLayer& getInstance();
    void discoverHardware();
    std::vector<std::shared_ptr<HardwareDevice>> getAvailableDevices();
    std::string generateCapabilityProfile();
    std::shared_ptr<HardwareDevice> getBestDeviceForTask(const std::string& taskType, size_t modelSize);

private:
    HardwareAbstractionLayer() = default;
    std::vector<std::shared_ptr<HardwareDevice>> m_devices;
};

} // namespace hal
} // namespace nanoai
#endif
