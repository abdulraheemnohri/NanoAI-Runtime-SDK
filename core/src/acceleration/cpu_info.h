#ifndef NANOAI_CPU_INFO_H
#define NANOAI_CPU_INFO_H

#include <string>

namespace nanoai {

enum class CpuArch {
    UNKNOWN,
    X86_64,
    ARM64,
    ARMV7
};

class CpuInfo {
public:
    static CpuArch getArchitecture();
    static std::string getArchitectureName();
};

} // namespace nanoai

#endif // NANOAI_CPU_INFO_H
