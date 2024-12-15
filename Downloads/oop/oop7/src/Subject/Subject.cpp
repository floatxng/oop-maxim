#include "Subject/Subject.h"

void Subject::AddObserver(const std::shared_ptr<IObserver>& obs) {
    observers.push_back(obs);
}

void Subject::RemoveObserver(const std::shared_ptr<IObserver>& obs) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), obs), 
        observers.end()
    );
}

void Subject::Notify(const std::string& message) {
    for (const auto& obs : observers) {
        if (obs) {
            obs->Update(message);
        }
    }
}
