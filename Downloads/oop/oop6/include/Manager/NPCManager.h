#pragma once
#include "../NPC/NPC.h"
#include "../Factory/NPCFactory.h"
#include "../Observer/IObserver.h"
#include "../Visitor/BattleVisitor.h"
#include <vector>
#include <memory>
#include <map>
#include <string>

class NPCManager {
private:
    std::vector<std::shared_ptr<NPC>> storage; // Коллекция NPC
    NPCFactory& factory; // Фабрика для создания NPC

    std::map<std::string, bool> usedNames; // Контроль уникальности имён

public:
    NPCManager(NPCFactory& f);

    bool AddNPC(const std::string& type, const std::string& name, float x, float y);
    void RemoveDeadNPCs();
    const std::vector<std::shared_ptr<NPC>>& GetNPCs() const;
    void AddObserverToAll(const std::shared_ptr<IObserver>& observer);
    void PrintAll() const;
    void StartBattle(float range);
    void Clear();
};
