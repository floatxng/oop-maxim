#pragma once
#include "IObserver.h"

class ConsoleLogger : public IObserver {
public:
    void Update(const std::string& message) override;
};
