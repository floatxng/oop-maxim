#include "NPC/NPC.h"

NPC::NPC(const std::string& _name, float _x, float _y, const NPCTypeInfo& tinfo)
    : name(_name), x(_x), y(_y), alive(true), info(tinfo) {}

const std::string& NPC::GetName() const { return name; }
float NPC::GetX() const { return x; }
float NPC::GetY() const { return y; }
bool NPC::IsAlive() const { return alive; }
std::string NPC::GetType() const { return info.typeName; }
int NPC::GetMoveRange() const { return info.moveRange; }
int NPC::GetKillRange() const { return info.killRange; }

void NPC::Kill() {
    if (alive) {
        alive = false;
        Notify("NPC " + name + " (" + GetType() + ") был убит!");
    }
}

float NPC::DistanceTo(const NPC& other) const {
    float dx = other.GetX() - x;
    float dy = other.GetY() - y;
    return std::sqrt(dx * dx + dy * dy);
}

int NPC::RollDice(std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(1,6);
    return dist(rng);
}

void NPC::MoveRandom(std::mt19937& rng, int mapWidth, int mapHeight) {
    if (!alive) return;
    std::uniform_int_distribution<int> dist(-GetMoveRange(), GetMoveRange());
    int dx = dist(rng);
    int dy = dist(rng);

    float newX = x + dx;
    float newY = y + dy;

    // Не покидаем карту
    if (newX < 0) newX = 0;
    if (newX > mapWidth) newX = static_cast<float>(mapWidth);
    if (newY < 0) newY = 0;
    if (newY > mapHeight) newY = static_cast<float>(mapHeight);

    x = newX;
    y = newY;
}
