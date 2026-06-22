#ifndef NANOAI_BACKEND_H
#define NANOAI_BACKEND_H

#include <string>
#include "nanoai/ai_task.h"

namespace nanoai {

class Backend {
public:
    virtual ~Backend() = default;
    virtual bool load(const std::string& modelPath) = 0;
    virtual std::string generate(const std::string& prompt) = 0;
    virtual std::string runTask(const AiTask& task) = 0;
    virtual std::string getName() const = 0;
};

} // namespace nanoai

#endif // NANOAI_BACKEND_H
