#include "NPC/Bull.h"
#include "Visitor/IVisitor.h"

Bull::Bull(const std::string& name, float x, float y, const NPCTypeInfo& info)
    : NPC(name, x, y, info) {}

void Bull::Accept(IVisitor& visitor) {
    visitor.Visit(*this);
}

std::string Bull::GetType() const {
    return "Bull";
}
