#ifndef NANOAI_EXECUTOR_H
#define NANOAI_EXECUTOR_H
namespace nanoai { namespace engine {
class Executor {
public:
    virtual void execute() = 0;
};
} }
#endif
