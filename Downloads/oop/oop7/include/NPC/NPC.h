#pragma once
#include "Subject/Subject.h"
#include <string>
#include <memory>
#include <random>
#include <cmath>

class IVisitor;

struct NPCTypeInfo {
    std::string typeName;
    int moveRange;
    int killRange;
};

class NPC : public Subject, public std::enable_shared_from_this<NPC> {
protected:
    std::string name;
    float x, y;
    bool alive;
    NPCTypeInfo info;
public:
    NPC(const std::string& _name, float _x, float _y, const NPCTypeInfo& tinfo);

    const std::string& GetName() const;
    float GetX() const;
    float GetY() const;
    bool IsAlive() const;
    std::string GetType() const;
    int GetMoveRange() const;
    int GetKillRange() const;

    virtual void Accept(IVisitor& visitor) = 0;

    virtual void Kill();
    float DistanceTo(const NPC& other) const;

    static int RollDice(std::mt19937& rng);

    void MoveRandom(std::mt19937& rng, int mapWidth, int mapHeight);
};
