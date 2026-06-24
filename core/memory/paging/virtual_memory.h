#ifndef NANOAI_VIRTUAL_MEMORY_H
#define NANOAI_VIRTUAL_MEMORY_H
#include <string>
namespace nanoai { namespace memory {
class VirtualMemory {
public:
    static void pageOut(const std::string& modelId);
    static void pageIn(const std::string& modelId);
};
} }
#endif
