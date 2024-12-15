#pragma once
#include "NPC.h"

class Dragon : public NPC {
public:
    Dragon(const std::string& name, float x, float y, const NPCTypeInfo& info);
    void Accept(IVisitor& visitor) override;
    std::string GetType() const;
};
