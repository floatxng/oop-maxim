#pragma once
#include "NPC/NPC.h"
#include "Factory/NPCFactory.h"
#include "Observer/IObserver.h"
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <shared_mutex>

class NPCManager {
private:
    std::vector<std::shared_ptr<NPC>> storage;
    NPCFactory& factory;
    std::map<std::string, bool> usedNames;
    mutable std::shared_mutex npcMutex;

public:
    NPCManager(NPCFactory& f);

    bool AddNPC(const std::string& type, const std::string& name, float x, float y);
    void RemoveDeadNPCs();
    std::vector<std::shared_ptr<NPC>> GetNPCs() const;
    void AddObserverToAll(const std::shared_ptr<IObserver>& observer);
    void PrintAll() const;
    void Clear();
};
