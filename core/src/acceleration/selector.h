#ifndef NANOAI_SELECTOR_H
#define NANOAI_SELECTOR_H

#include "device.h"
#include <memory>

namespace nanoai {

class SmartRuntimeSelector {
public:
    static DeviceType selectBestDevice();
    static std::vector<DeviceCapability> getAvailableDevices();
};

} // namespace nanoai

#endif // NANOAI_SELECTOR_H
