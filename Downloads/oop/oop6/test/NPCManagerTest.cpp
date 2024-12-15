#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <cstdio>

#include "Factory/NPCFactory.h"
#include "Observer/IObserver.h"
#include "Observer/ConsoleLogger.h"
#include "Observer/FileLogger.h"
#include "Manager/NPCManager.h"
#include "Manager/PersistenceManager.h"
#include "NPC/Dragon.h"
#include "NPC/Bull.h"
#include "NPC/Frog.h"

class MockObserver : public IObserver {
public:
    std::vector<std::string> messages;

    void Update(const std::string& message) override {
        messages.push_back(message);
    }
};

void RegisterNPCTypes(NPCFactory& factory) {
    factory.RegisterNPC("Dragon", [](const std::string& name, float x, float y) -> std::shared_ptr<NPC> {
        return std::make_shared<Dragon>(name, x, y);
    });
    factory.RegisterNPC("Bull", [](const std::string& name, float x, float y) -> std::shared_ptr<NPC> {
        return std::make_shared<Bull>(name, x, y);
    });
    factory.RegisterNPC("Frog", [](const std::string& name, float x, float y) -> std::shared_ptr<NPC> {
        return std::make_shared<Frog>(name, x, y);
    });
}

class NPCManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        RegisterNPCTypes(factory);
    }

    void TearDown() override {
        std::remove("test_saves/npcs_test.txt");
        std::remove("test_logs/log_test.txt");
    }

    NPCFactory factory;
    NPCManager manager{factory};
    PersistenceManager persistence{factory};
};

TEST_F(NPCManagerTest, AddNPC_Success) {
    bool added;

    added = manager.AddNPC("Dragon", "Smaug", 100, 100);
    EXPECT_TRUE(added);

    added = manager.AddNPC("Bull", "Ferdinand", 105, 101);
    EXPECT_TRUE(added);

    added = manager.AddNPC("Frog", "Kermit", 108, 102);
    EXPECT_TRUE(added);
}

TEST_F(NPCManagerTest, AddNPC_DuplicateName) {
    bool added;

    added = manager.AddNPC("Dragon", "Smaug", 100, 100);
    EXPECT_TRUE(added);

    added = manager.AddNPC("Bull", "Smaug", 150, 150);
    EXPECT_FALSE(added);
}

TEST_F(NPCManagerTest, AddNPC_InvalidCoordinates) {
    bool added;

    added = manager.AddNPC("Dragon", "Smaug", -10, 100);
    EXPECT_FALSE(added);

    added = manager.AddNPC("Bull", "Toro", 600, 200);
    EXPECT_FALSE(added);

    added = manager.AddNPC("Frog", "Kermit", 100, -5);
    EXPECT_FALSE(added);

    added = manager.AddNPC("Frog", "Freddy", 200, 700);
    EXPECT_FALSE(added);
}

TEST_F(NPCManagerTest, AddNPC_UnknownType) {
    bool added;

    added = manager.AddNPC("UnknownType", "Mystery", 100, 100);
    EXPECT_FALSE(added);
}

TEST_F(NPCManagerTest, BattleMode_SimpleBattle) {
    manager.AddNPC("Dragon", "Smaug", 100, 100);
    manager.AddNPC("Bull", "Ferdinand", 105, 101);
    manager.AddNPC("Frog", "Kermit", 108, 102);
    manager.AddNPC("Bull", "Toro", 200, 200);
    manager.AddNPC("Frog", "Freddy", 202, 202);

    auto mockObserver = std::make_shared<MockObserver>();
    manager.AddObserverToAll(mockObserver);

    manager.StartBattle(10.0f);

    EXPECT_EQ(mockObserver->messages.size(), 2);
    EXPECT_NE(std::find(mockObserver->messages.begin(), mockObserver->messages.end(),
                        "NPC Ferdinand (Bull) был убит!"), mockObserver->messages.end());
    EXPECT_NE(std::find(mockObserver->messages.begin(), mockObserver->messages.end(),
                        "NPC Kermit (Frog) был убит!"), mockObserver->messages.end());

    const auto& npcs = manager.GetNPCs();
    ASSERT_EQ(npcs.size(), 3);
    EXPECT_EQ(npcs[0]->GetName(), "Smaug");
    EXPECT_EQ(npcs[1]->GetName(), "Toro");
    EXPECT_EQ(npcs[2]->GetName(), "Freddy");
}

TEST_F(NPCManagerTest, SaveAndLoadNPCs) {
    manager.AddNPC("Dragon", "Smaug", 100, 100);
    manager.AddNPC("Bull", "Ferdinand", 105, 101);
    manager.AddNPC("Frog", "Kermit", 108, 102);
    manager.AddNPC("Bull", "Toro", 200, 200);
    manager.AddNPC("Frog", "Freddy", 202, 202);

    manager.StartBattle(10.0f);

    std::string saveFile = "test_saves/npcs_test.txt";
    persistence.SaveToFile(saveFile, manager.GetNPCs());

    manager.Clear();
    EXPECT_EQ(manager.GetNPCs().size(), 0);

    persistence.LoadFromFile(saveFile, manager);

    const auto& npcs = manager.GetNPCs();
    ASSERT_EQ(npcs.size(), 3);

    EXPECT_EQ(npcs[0]->GetName(), "Smaug");
    EXPECT_TRUE(npcs[0]->IsAlive());

    EXPECT_EQ(npcs[1]->GetName(), "Toro");
    EXPECT_TRUE(npcs[1]->IsAlive());

    EXPECT_EQ(npcs[2]->GetName(), "Freddy");
    EXPECT_TRUE(npcs[2]->IsAlive());

}

TEST_F(NPCManagerTest, Observers_ReceiveNotifications) {
    manager.AddNPC("Dragon", "Smaug", 100, 100);
    manager.AddNPC("Bull", "Ferdinand", 105, 101);
    manager.AddNPC("Frog", "Kermit", 108, 102);

    auto mockObserver = std::make_shared<MockObserver>();
    manager.AddObserverToAll(mockObserver);

    manager.StartBattle(10.0f);

    EXPECT_EQ(mockObserver->messages.size(), 2);
    EXPECT_NE(std::find(mockObserver->messages.begin(), mockObserver->messages.end(),
                        "NPC Ferdinand (Bull) был убит!"), mockObserver->messages.end());
    EXPECT_NE(std::find(mockObserver->messages.begin(), mockObserver->messages.end(),
                        "NPC Kermit (Frog) был убит!"), mockObserver->messages.end());
}

TEST_F(NPCManagerTest, FileLogger_LogsCorrectly) {
    auto fileLogger = std::make_shared<FileLogger>("test_logs/log_test.txt");
    manager.AddObserverToAll(fileLogger);

    manager.AddNPC("Dragon", "Smaug", 100, 100);
    manager.AddNPC("Bull", "Ferdinand", 105, 101);
    manager.AddNPC("Frog", "Kermit", 108, 102);

    manager.StartBattle(10.0f);

    fileLogger.reset();

    std::ifstream logFile("test_logs/log_test.txt");
    ASSERT_TRUE(logFile.is_open());

    std::vector<std::string> logMessages;
    std::string line;
    while (std::getline(logFile, line)) {
        logMessages.push_back(line);
    }
    logFile.close();

    ASSERT_EQ(logMessages.size(), 2);
    EXPECT_EQ(logMessages[0], "NPC Ferdinand (Bull) был убит!");
    EXPECT_EQ(logMessages[1], "NPC Kermit (Frog) был убит!");
}
