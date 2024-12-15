#include "Manager/PersistenceManager.h"
#include "NPC/NPC.h"
#include "NPC/Dragon.h"
#include "NPC/Bull.h"
#include "NPC/Frog.h"
#include "Manager/NPCManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>

PersistenceManager::PersistenceManager(NPCFactory& f) : factory(f) {}

void PersistenceManager::SaveToFile(const std::string& filename, const std::vector<std::shared_ptr<NPC>>& npcs) const {
    std::filesystem::path savePath = std::filesystem::path(filename).parent_path();

    if (!std::filesystem::exists(savePath)) {
        std::filesystem::create_directories(savePath);
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для сохранения: " + filename);
    }

    for (const auto& npc : npcs) {
        file << npc->GetType() << " " << npc->GetName() << " " << npc->GetX() << " " << npc->GetY() << "\n";
    }

    file.close();
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
            if(!alive) {
                auto& npcs = manager.GetNPCs();
                if(!npcs.empty()) {
                    npcs.back()->Kill();
                }
            }
        }
    }
}
