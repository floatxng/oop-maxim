#pragma once
#include "IVisitor.h"
#include "../NPC/NPC.h"
#include <vector>
#include <memory>

class BattleVisitor : public IVisitor {
    std::vector<std::shared_ptr<NPC>>& npcs;
    float battleRange;
public:
    BattleVisitor(std::vector<std::shared_ptr<NPC>>& _npcs, float range);
    void Visit(Dragon& npc) override;
    void Visit(Bull& npc) override;
    void Visit(Frog& npc) override;
};
