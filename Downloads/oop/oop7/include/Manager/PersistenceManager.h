#pragma once
#include "../NPC/NPC.h"
#include "../Factory/NPCFactory.h"
#include "NPCManager.h"
#include <string>
#include <vector>
#include <memory>

class PersistenceManager {
private:
    NPCFactory& factory;

public:
    PersistenceManager(NPCFactory& f);

    void SaveToFile(const std::string& filename, const std::vector<std::shared_ptr<NPC>>& npcs) const;
    void LoadFromFile(const std::string& filename, NPCManager& manager) const;
};
