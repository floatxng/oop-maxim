#include "Factory/NPCFactory.h"

void NPCFactory::RegisterNPC(const std::string& type, CreatorFunc func) {
    creators[type] = func;
}

std::shared_ptr<NPC> NPCFactory::CreateNPC(const std::string& type, const std::string& name, float x, float y) const {
    auto it = creators.find(type);
    if(it != creators.end()) {
        return it->second(name, x, y);
    }
    return nullptr;
}
