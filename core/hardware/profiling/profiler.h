#ifndef NANOAI_PROFILER_H
#define NANOAI_PROFILER_H

#include <string>

namespace nanoai {
namespace hardware {

class Profiler {
public:
    static void profileDevice(const std::string& deviceId);
};

} }
#endif
