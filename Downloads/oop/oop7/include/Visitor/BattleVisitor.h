#pragma once
#include "IVisitor.h"
#include "../NPC/NPC.h"
#include <vector>
#include <memory>
#include <random>

class BattleVisitor : public IVisitor {
private:
    std::vector<std::shared_ptr<NPC>>& npcs;
    float battleRange;
    std::mt19937& rng;

    bool AttemptKill(NPC& attacker, NPC& defender);

public:
    BattleVisitor(std::vector<std::shared_ptr<NPC>>& _npcs, float range, std::mt19937& _rng);
    void Visit(Dragon& npc) override;
    void Visit(Bull& npc) override;
    void Visit(Frog& npc) override;
};
