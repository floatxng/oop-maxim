#pragma once
#include "NPC.h"

class Bull : public NPC {
public:
    Bull(const std::string& name, float x, float y, const NPCTypeInfo& info);
    void Accept(IVisitor& visitor) override;
    std::string GetType() const;
};
