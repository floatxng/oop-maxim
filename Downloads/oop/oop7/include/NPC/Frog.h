#pragma once
#include "NPC/NPC.h"

class Frog : public NPC {
public:
    Frog(const std::string& name, float x, float y, const NPCTypeInfo& info);
    void Accept(IVisitor& visitor) override;
    std::string GetType() const;
};
