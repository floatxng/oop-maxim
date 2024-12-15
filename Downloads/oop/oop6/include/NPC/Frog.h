#pragma once
#include "NPC.h"

class Frog : public NPC {
public:
    Frog(const std::string& name, float x, float y);
    std::string GetType() const override;
    void Accept(IVisitor& visitor) override;
};
