#include "garbage_collector.h"
#include <iostream>
namespace nanoai { namespace memory {
void GarbageCollector::runPass() {
    std::cout << "[GC] Reclaiming unused model buffers..." << std::endl;
}
} }
