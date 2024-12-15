#pragma once
#include "NPC.h"

class Bull : public NPC {
public:
    Bull(const std::string& name, float x, float y);
    std::string GetType() const override;
    void Accept(IVisitor& visitor) override;
};
