#include "NPC/Bull.h"
#include "Visitor/IVisitor.h"

Bull::Bull(const std::string& name, float x, float y)
    : NPC(name, x, y) {}

std::string Bull::GetType() const {
    return "Bull";
}

void Bull::Accept(IVisitor& visitor) {
    visitor.Visit(*this);
}
