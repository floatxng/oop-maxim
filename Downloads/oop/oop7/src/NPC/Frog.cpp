#include "NPC/Frog.h"
#include "Visitor/IVisitor.h"

Frog::Frog(const std::string& name, float x, float y, const NPCTypeInfo& info)
    : NPC(name, x, y, info) {}

void Frog::Accept(IVisitor& visitor) {
    visitor.Visit(*this);
}

std::string Frog::GetType() const {
    return "Frog";
}
