#ifndef NANOAI_PRIORITY_QUEUE_H
#define NANOAI_PRIORITY_QUEUE_H
#include <queue>
#include <vector>
namespace nanoai { namespace scheduler {
template<typename T>
class PriorityQueue {
    std::priority_queue<T> m_queue;
};
} }
#endif
