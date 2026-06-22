#ifndef NANOAI_DEVICE_H
#define NANOAI_DEVICE_H

#include <string>
#include <vector>

namespace nanoai {

enum class DeviceType {
    CPU,
    GPU,
    NPU
};

struct DeviceCapability {
    DeviceType type;
    std::string name;
    float score; // Higher is better
    bool is_available;
};

} // namespace nanoai

#endif // NANOAI_DEVICE_H
