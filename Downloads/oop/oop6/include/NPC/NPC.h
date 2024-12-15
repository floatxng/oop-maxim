#pragma once
#include "../Subject/Subject.h"
#include <string>
#include <memory>

class IVisitor; // Предварительное объявление

class NPC : public Subject, public std::enable_shared_from_this<NPC> {
protected:
    std::string name;
    float x, y;
    bool alive;
public:
    NPC(const std::string& _name, float _x, float _y);
    virtual ~NPC() = default;

    const std::string& GetName() const;
    float GetX() const;
    float GetY() const;
    bool IsAlive() const;

    virtual std::string GetType() const = 0;
    virtual void Accept(IVisitor& visitor) = 0;

    virtual void Kill();
    float DistanceTo(const std::shared_ptr<NPC>& other) const;
};
