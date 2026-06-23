#include "cpu_info.h"

#if defined(__x86_64__) || defined(_M_X64)
    #define NANOAI_ARCH_X86_64
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define NANOAI_ARCH_ARM64
#elif defined(__arm__) || defined(_M_ARM)
    #define NANOAI_ARCH_ARMV7
#endif

namespace nanoai {

CpuArch CpuInfo::getArchitecture() {
#if defined(NANOAI_ARCH_X86_64)
    return CpuArch::X86_64;
#elif defined(NANOAI_ARCH_ARM64)
    return CpuArch::ARM64;
#elif defined(NANOAI_ARCH_ARMV7)
    return CpuArch::ARMV7;
#else
    return CpuArch::UNKNOWN;
#endif
}

std::string CpuInfo::getArchitectureName() {
    switch (getArchitecture()) {
        case CpuArch::X86_64: return "x86_64";
        case CpuArch::ARM64: return "ARM64";
        case CpuArch::ARMV7: return "ARMv7";
        default: return "Unknown";
    }
}

} // namespace nanoai
