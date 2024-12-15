#include "Manager/NPCManager.h"
#include <iostream>
#include <algorithm>
#include <mutex>

NPCManager::NPCManager(NPCFactory& f) : factory(f) {}

bool NPCManager::AddNPC(const std::string& type, const std::string& name, float x, float y) {
    if(x < 0 || x > 100 || y < 0 || y > 100) {
        std::cout << "Координаты вне допустимого диапазона!\n";
        return false;
    }

    if(usedNames.find(name) != usedNames.end()) {
        std::cout << "Имя уже занято!\n";
        return false;
    }

    auto npc = factory.CreateNPC(type, name, x, y);
    if(!npc) {
        std::cout << "Неизвестный тип NPC!\n";
        return false;
    }

    {
        std::unique_lock<std::shared_mutex> lock(npcMutex);
        storage.push_back(npc);
    }
    usedNames[name] = true;
    return true;
}

void NPCManager::RemoveDeadNPCs() {
    std::unique_lock<std::shared_mutex> lock(npcMutex);
    storage.erase(std::remove_if(storage.begin(), storage.end(),
        [](const std::shared_ptr<NPC>& n){ return !n->IsAlive(); }), storage.end());
}

std::vector<std::shared_ptr<NPC>> NPCManager::GetNPCs() const {
    std::shared_lock<std::shared_mutex> lock(npcMutex);
    return storage;
}

void NPCManager::AddObserverToAll(const std::shared_ptr<IObserver>& observer) {
    std::shared_lock<std::shared_mutex> lock(npcMutex);
    for(auto& npc : storage) {
        npc->AddObserver(observer);
    }
}

void NPCManager::PrintAll() const {
    std::shared_lock<std::shared_mutex> lock(npcMutex);
    for(const auto& npc : storage) {
        std::cout << "NPC: " << npc->GetName() << " ("
                  << npc->GetType() << ") at ("
                  << npc->GetX() << ", " << npc->GetY() << ")"
                  << (npc->IsAlive() ? " [Alive]" : " [Dead]")
                  << std::endl;
    }
}

void NPCManager::Clear() {
    std::unique_lock<std::shared_mutex> lock(npcMutex);
    storage.clear();
    usedNames.clear();
}
