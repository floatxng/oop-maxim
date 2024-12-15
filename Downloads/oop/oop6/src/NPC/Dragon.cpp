#include "NPC/Dragon.h"
#include "Visitor/IVisitor.h"

Dragon::Dragon(const std::string& name, float x, float y)
    : NPC(name, x, y) {}

std::string Dragon::GetType() const {
    return "Dragon";
}

void Dragon::Accept(IVisitor& visitor) {
    visitor.Visit(*this);
}
