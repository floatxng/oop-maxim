#include "Controller/GameEngine.h"
#include <iostream>
#include <vector>
#include <thread>
#include <Observer/ConsoleLogger.h>

static const int MAP_WIDTH = 100;
static const int MAP_HEIGHT = 100;

GameEngine::GameEngine(NPCFactory& factory, NPCManager& manager, std::shared_ptr<IObserver> logger)
    : npcFactory(factory), npcManager(manager), logger(logger), running(false), rng(std::random_device{}()) {}

void GameEngine::InitializeNPCs(int count) {
    std::uniform_int_distribution<int> distX(0, MAP_WIDTH);
    std::uniform_int_distribution<int> distY(0, MAP_HEIGHT);
    std::uniform_int_distribution<int> typeDist(0,2);
    std::array<NPCTypeInfo,3> types = { 
        NPCTypeInfo{"Bull", 30, 10}, 
        NPCTypeInfo{"Frog", 1, 10}, 
        NPCTypeInfo{"Dragon", 50, 30} 
    };

    for (int i = 0; i < count; ++i) {
        NPCTypeInfo t = types[typeDist(rng)];
        std::string name = t.typeName + std::to_string(i);
        float x = static_cast<float>(distX(rng));
        float y = static_cast<float>(distY(rng));
        if(npcManager.AddNPC(t.typeName, name, x, y)) {
        }
    }

    npcManager.AddObserverToAll(logger);
}

void GameEngine::PrintMap() {
    std::lock_guard<std::mutex> guard(ConsoleLogger::consoleMutex);
    std::cout << "\033[2J\033[H";
    std::cout << "Карта (живые NPC):" << std::endl;

    auto npcs = npcManager.GetNPCs();
    std::vector<std::string> map(MAP_HEIGHT+1, std::string(MAP_WIDTH+1, '.'));

    for (auto& npc : npcs) {
        if (npc->IsAlive()) {
            int nx = static_cast<int>(npc->GetX());
            int ny = static_cast<int>(npc->GetY());
            char c = '?';
            std::string type = npc->GetType();
            if (type == "Bull") c = 'B';
            else if (type == "Frog") c = 'F';
            else if (type == "Dragon") c = 'D';

            if (nx >=0 && nx <= MAP_WIDTH && ny >=0 && ny <= MAP_HEIGHT) {
                map[ny][nx] = c;
            }
        }
    }

    for (const auto& line : map) {
        std::cout << line << "\n";
    }
}

void GameEngine::Start() {
    running = true;
    auto gameTask = Run();

    auto startTime = std::chrono::steady_clock::now();
    auto lastPrintTime = startTime;

    while (running) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        if (elapsed >= 30) {
            Stop();
            break;
        }

        gameTask.resume();

        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastPrintTime).count();
        if (delta >= 1000) {
            PrintMap();
            lastPrintTime = currentTime;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    PrintMap();

    {
        std::lock_guard<std::mutex> guard(ConsoleLogger::consoleMutex);
        std::cout << std::endl << "Игра окончена! Выжившие NPC:" << std::endl;
        auto npcs = npcManager.GetNPCs();
        for (auto& npc : npcs) {
            if (npc->IsAlive()) {
                std::cout << npc->GetName() << " (" << npc->GetType() << ") at (" << npc->GetX() << "," << npc->GetY() << ")\n";
            }
        }
    }
}

void GameEngine::Stop() {
    running = false;
}

GameTask GameEngine::Run() {
    while (running) {
        {
            std::lock_guard<std::mutex> lock(gameMutex);
            auto npcs = npcManager.GetNPCs();
            for (auto& npc : npcs) {
                if (npc->IsAlive()) {
                    npc->MoveRandom(rng, MAP_WIDTH, MAP_HEIGHT);
                }
            }

            auto npcsCopy = npcManager.GetNPCs();
            BattleVisitor visitor(npcsCopy, 50.0f, rng);
            for (auto& npc : npcsCopy) {
                if (npc->IsAlive()) {
                    npc->Accept(visitor);
                }
            }

            npcManager.RemoveDeadNPCs();
        }

        co_yield 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
