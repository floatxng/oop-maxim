#include "Visitor/BattleVisitor.h"
#include "NPC/Dragon.h"
#include "NPC/Bull.h"
#include "NPC/Frog.h"

BattleVisitor::BattleVisitor(std::vector<std::shared_ptr<NPC>>& _npcs, float range)
    : npcs(_npcs), battleRange(range) {}

void BattleVisitor::Visit(Dragon& dragon) {
    for(auto& other : npcs) {
        if(other->IsAlive() && other->GetType() == "Bull") {
            float dist = dragon.DistanceTo(other);
            if(dist <= battleRange) {
                other->Kill();
            }
        }
    }
}

void BattleVisitor::Visit(Bull& bull) {
    for(auto& other : npcs) {
        if(other->IsAlive() && other->GetType() == "Frog") {
            float dist = bull.DistanceTo(other);
            if(dist <= battleRange) {
                other->Kill();
            }
        }
    }
}

void BattleVisitor::Visit(Frog& frog) {
    // Жабы не атакуют
}
