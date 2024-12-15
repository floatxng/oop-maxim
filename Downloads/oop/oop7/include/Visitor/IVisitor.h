#pragma once
#include "NPC/Bull.h"
#include "NPC/Dragon.h"
#include "NPC/Frog.h"

class IVisitor {
public:
    virtual ~IVisitor() = default;
    virtual void Visit(Dragon& npc) = 0;
    virtual void Visit(Bull& npc) = 0;
    virtual void Visit(Frog& npc) = 0;
};
