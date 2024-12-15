#pragma once
#include <string>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void Update(const std::string& message) = 0;
};
