#pragma once
#include "NPC.h"

class Dragon : public NPC {
public:
    Dragon(const std::string& name, float x, float y);
    std::string GetType() const override;
    void Accept(IVisitor& visitor) override;
};
