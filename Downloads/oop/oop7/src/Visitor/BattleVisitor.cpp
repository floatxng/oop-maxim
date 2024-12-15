#include "Visitor/BattleVisitor.h"
#include "NPC/Dragon.h"
#include "NPC/Bull.h"
#include "NPC/Frog.h"

BattleVisitor::BattleVisitor(std::vector<std::shared_ptr<NPC>>& _npcs, float range, std::mt19937& _rng)
    : npcs(_npcs), battleRange(range), rng(_rng) {}

bool BattleVisitor::AttemptKill(NPC& attacker, NPC& defender) {
    if (!defender.IsAlive()) return false;
    float distance = attacker.DistanceTo(defender);
    if (distance <= attacker.GetKillRange() && distance > 0) {
        int attack = NPC::RollDice(rng);
        int defense = NPC::RollDice(rng);
        if (attack > defense) {
            defender.Kill();
            return true;
        }
    }
    return false;
}

void BattleVisitor::Visit(Dragon& npc) {
    if (!npc.IsAlive()) return;
    for (auto& target : npcs) {
        if (target->GetType() != "Dragon" && target->IsAlive()) {
            AttemptKill(npc, *target);
        }
    }
}

void BattleVisitor::Visit(Bull& npc) {
    if (!npc.IsAlive()) return;
    for (auto& target : npcs) {
        if (target->GetType() != "Bull" && target->IsAlive()) {
            AttemptKill(npc, *target);
        }
    }
}

void BattleVisitor::Visit(Frog& npc) {
    if (!npc.IsAlive()) return;
    for (auto& target : npcs) {
        if (target->GetType() != "Frog" && target->IsAlive()) {
            AttemptKill(npc, *target);
        }
    }
}
