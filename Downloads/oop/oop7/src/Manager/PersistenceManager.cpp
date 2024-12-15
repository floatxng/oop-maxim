#include "Manager/PersistenceManager.h"
#include <fstream>
#include <iostream>

PersistenceManager::PersistenceManager(NPCFactory& f) : factory(f) {}

void PersistenceManager::SaveToFile(const std::string& filename, const std::vector<std::shared_ptr<NPC>>& npcs) const {
    std::ofstream ofs(filename);
    if(!ofs) {
        std::cerr << "Не удалось открыть файл для сохранения: " << filename << std::endl;
        return;
    }

    for(const auto& npc : npcs) {
        ofs << npc->GetType() << " "
            << npc->GetName() << " "
            << npc->GetX() << " "
            << npc->GetY() << " "
            << npc->IsAlive() << "\n";
    }
}

void PersistenceManager::LoadFromFile(const std::string& filename, NPCManager& manager) const {
    std::ifstream ifs(filename);
    if(!ifs) {
        std::cerr << "Не удалось открыть файл для загрузки: " << filename << std::endl;
        return;
    }

    manager.Clear();

    std::string type, name;
    float x, y;
    bool alive;
    while(ifs >> type >> name >> x >> y >> alive) {
        if(manager.AddNPC(type, name, x, y)) {
            auto npcs = manager.GetNPCs();
            if(!alive && !npcs.empty()) {
                npcs.back()->Kill();
            }
        }
    }
}
