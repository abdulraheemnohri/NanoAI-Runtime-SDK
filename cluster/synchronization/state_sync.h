#ifndef NANOAI_STATE_SYNC_H
#define NANOAI_STATE_SYNC_H
#include <string>
namespace nanoai { namespace cluster {
class StateSync {
public:
    static void syncGlobalState();
};
} }
#endif
