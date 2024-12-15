#include "NPC/NPC.h"
#include <cmath>

NPC::NPC(const std::string& _name, float _x, float _y)
    : name(_name), x(_x), y(_y), alive(true) {}

const std::string& NPC::GetName() const {
    return name;
}

float NPC::GetX() const {
    return x;
}

float NPC::GetY() const {
    return y;
}

bool NPC::IsAlive() const {
    return alive;
}

void NPC::Kill() {
    if (alive) {
        alive = false;
        Notify("NPC " + name + " (" + GetType() + ") был убит!");
    }
}

float NPC::DistanceTo(const std::shared_ptr<NPC>& other) const {
    float dx = other->GetX() - x;
    float dy = other->GetY() - y;
    return std::sqrt(dx * dx + dy * dy);
}
