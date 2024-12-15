#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <random>
#include <mutex>
#include <chrono>
#include "Factory/NPCFactory.h"
#include "Observer/ConsoleLogger.h"
#include "Manager/NPCManager.h"
#include "Manager/PersistenceManager.h"
#include "NPC/Dragon.h"
#include "NPC/Bull.h"
#include "NPC/Frog.h"
#include "Controller/GameEngine.h"

int main() {
    try {
        NPCFactory factory;
        factory.RegisterNPC("Dragon", [](const std::string& name, float x, float y) -> std::shared_ptr<NPC> {
            return std::make_shared<Dragon>(name, x, y, NPCTypeInfo{"Dragon", 50, 30});
        });
        factory.RegisterNPC("Bull", [](const std::string& name, float x, float y) -> std::shared_ptr<NPC> {
            return std::make_shared<Bull>(name, x, y, NPCTypeInfo{"Bull", 30, 10});
        });
        factory.RegisterNPC("Frog", [](const std::string& name, float x, float y) -> std::shared_ptr<NPC> {
            return std::make_shared<Frog>(name, x, y, NPCTypeInfo{"Frog", 1, 10});
        });

        NPCManager manager(factory);

        auto consoleLog = std::make_shared<ConsoleLogger>();

        GameEngine gameEngine(factory, manager, consoleLog);

        gameEngine.InitializeNPCs(50);

        gameEngine.Start();

    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }

    return 0;
}
