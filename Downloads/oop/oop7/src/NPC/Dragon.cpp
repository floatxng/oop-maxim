#include "NPC/Dragon.h"
#include "Visitor/IVisitor.h"

Dragon::Dragon(const std::string& name, float x, float y, const NPCTypeInfo& info)
    : NPC(name, x, y, info) {}

void Dragon::Accept(IVisitor& visitor) {
    visitor.Visit(*this);
}

std::string Dragon::GetType() const {
    return "Dragon";
}
