#pragma once
#include <algorithm>
#include <vector>
#include <memory>
#include "Observer/IObserver.h"

class Subject {
    std::vector<std::shared_ptr<IObserver>> observers;
public:
    void AddObserver(const std::shared_ptr<IObserver>& obs);
    void RemoveObserver(const std::shared_ptr<IObserver>& obs);
protected:
    void Notify(const std::string& message);
};
