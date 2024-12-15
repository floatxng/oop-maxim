#pragma once

#include "Manager/NPCManager.h"
#include "Visitor/BattleVisitor.h"
#include "Factory/NPCFactory.h"
#include "Observer/IObserver.h"
#include <coroutine>
#include <atomic>
#include <random>
#include <chrono>
#include <mutex>

struct GameTask {
    struct promise_type {
        GameTask get_return_object() { return GameTask{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::terminate(); }
        void return_void() {}
        std::suspend_always yield_value(int) noexcept { return {}; }
    };

    std::coroutine_handle<promise_type> handle;
    GameTask(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~GameTask() { if (handle) handle.destroy(); }
    GameTask(const GameTask&) = delete;
    GameTask(GameTask&& other) : handle(other.handle) { other.handle = nullptr; }
    bool resume() {
        if (!handle.done()) {
            handle.resume();
            return !handle.done();
        }
        return false;
    }
};

class GameEngine {
public:
    GameEngine(NPCFactory& factory, NPCManager& manager, std::shared_ptr<IObserver> logger);
    GameTask Run();
    void InitializeNPCs(int count);
    void PrintMap();
    void Start();
    void Stop();

private:
    NPCFactory& npcFactory;
    NPCManager& npcManager;
    std::shared_ptr<IObserver> logger;
    std::atomic_bool running;
    std::mt19937 rng;
    std::mutex gameMutex;
};
