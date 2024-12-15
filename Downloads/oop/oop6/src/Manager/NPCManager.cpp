#include "Manager/NPCManager.h"
#include "Visitor/BattleVisitor.h"
#include <iostream>

NPCManager::NPCManager(NPCFactory& f) : factory(f) {}

bool NPCManager::AddNPC(const std::string& type, const std::string& name, float x, float y) {
    if(x < 0 || x > 500 || y < 0 || y > 500) {
        std::cout << "Координаты вне допустимого диапазона!" << std::endl;
        return false;
    }

    if(usedNames.find(name) != usedNames.end()) {
        std::cout << "Имя уже занято!" << std::endl;
        return false;
    }

    auto npc = factory.CreateNPC(type, name, x, y);
    if(!npc) {
        std::cout << "Неизвестный тип NPC!" << std::endl;
        return false;
    }

    storage.push_back(npc);
    usedNames[name] = true;
    return true;
}

void NPCManager::RemoveDeadNPCs() {
    storage.erase(std::remove_if(storage.begin(), storage.end(),
        [](const std::shared_ptr<NPC>& n) { return !n->IsAlive(); }),
        storage.end());
}

const std::vector<std::shared_ptr<NPC>>& NPCManager::GetNPCs() const {
    return storage;
}

void NPCManager::AddObserverToAll(const std::shared_ptr<IObserver>& observer) {
    for(auto& npc : storage) {
        npc->AddObserver(observer);
    }
}

void NPCManager::PrintAll() const {
    for(const auto& npc : storage) {
        std::cout << "NPC: " << npc->GetName() << " ("
                  << npc->GetType() << ") at ("
                  << npc->GetX() << ", " << npc->GetY() << ")"
                  << (npc->IsAlive() ? " [Alive]" : " [Dead]")
                  << std::endl;
    }
}

void NPCManager::StartBattle(float range) {
    BattleVisitor visitor(const_cast<std::vector<std::shared_ptr<NPC>>&>(storage), range);
    for(auto& npc : storage) {
        if(npc->IsAlive()) {
            npc->Accept(visitor);
        }
    }
    RemoveDeadNPCs();
}

void NPCManager::Clear() {
    storage.clear();
    usedNames.clear();
}
