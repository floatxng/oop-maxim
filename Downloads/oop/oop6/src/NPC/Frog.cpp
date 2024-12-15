#include "NPC/Frog.h"
#include "Visitor/IVisitor.h"

Frog::Frog(const std::string& name, float x, float y)
    : NPC(name, x, y) {}

std::string Frog::GetType() const {
    return "Frog";
}

void Frog::Accept(IVisitor& visitor) {
    visitor.Visit(*this);
}
