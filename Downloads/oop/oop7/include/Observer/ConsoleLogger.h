#pragma once
#include "IObserver.h"
#include <mutex>

class ConsoleLogger : public IObserver {
public:
    void Update(const std::string& message) override;
    static std::mutex consoleMutex;
};
