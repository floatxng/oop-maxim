#include <iostream>
#include <memory>
#include "Factory/NPCFactory.h"
#include "Observer/ConsoleLogger.h"
#include "Observer/FileLogger.h"
#include "Manager/NPCManager.h"
#include "Manager/PersistenceManager.h"

// Функция для регистрации типов NPC
void RegisterNPCTypes(NPCFactory& factory) {
    factory.RegisterNPC("Dragon", [](const std::string& name, float x, float y) -> std::shared_ptr<NPC> {
        return std::static_pointer_cast<NPC>(std::make_shared<Dragon>(name, x, y));
    });
    factory.RegisterNPC("Bull", [](const std::string& name, float x, float y) -> std::shared_ptr<NPC> {
        return std::static_pointer_cast<NPC>(std::make_shared<Bull>(name, x, y));
    });
    factory.RegisterNPC("Frog", [](const std::string& name, float x, float y) -> std::shared_ptr<NPC> {
        return std::static_pointer_cast<NPC>(std::make_shared<Frog>(name, x, y));
    });
}

int main() {
    try {
        // Создаём фабрику и регистрируем типы NPC
        NPCFactory factory;
        RegisterNPCTypes(factory);

        // Создаём менеджер NPC
        NPCManager manager(factory);

        // Создаём менеджер для сохранения и загрузки
        PersistenceManager persistence(factory);

        // Создаём наблюдателей
        auto consoleLog = std::make_shared<ConsoleLogger>();
        auto fileLog = std::make_shared<FileLogger>("logs/log.txt");

        // Добавляем NPC
        manager.AddNPC("Dragon", "Smaug", 100, 100);
        manager.AddNPC("Bull",   "Ferdinand", 105, 101);
        manager.AddNPC("Frog",   "Kermit", 108, 102);
        manager.AddNPC("Bull",   "Toro", 200, 200);
        manager.AddNPC("Frog",   "Freddy", 202, 202);

        // Подписываем всех NPC на наблюдателей
        manager.AddObserverToAll(consoleLog);
        manager.AddObserverToAll(fileLog);

        std::cout << "Перед боем:" << std::endl;
        manager.PrintAll();

        // Запускаем боевой режим с радиусом 10 метров
        manager.StartBattle(10.0f);

        std::cout << "\nПосле боя:" << std::endl;
        manager.PrintAll();

        // Сохраняем текущее состояние
        persistence.SaveToFile("saves/npcs.txt", manager.GetNPCs());

        // Загрузка из файла (раскомментировать при необходимости)
        /*
        persistence.LoadFromFile("saves/npcs.txt", manager);
        std::cout << "\nПосле загрузки из файла:" << std::endl;
        manager.PrintAll();
        */

    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }

    return 0;
}
