#pragma once
#include "../NPC/NPC.h"
#include <string>
#include <memory>
#include <functional>
#include <map>

class NPCFactory {
public:
    using CreatorFunc = std::function<std::shared_ptr<NPC>(const std::string&, float, float)>;

    void RegisterNPC(const std::string& type, CreatorFunc func);
    std::shared_ptr<NPC> CreateNPC(const std::string& type, const std::string& name, float x, float y) const;

private:
    std::map<std::string, CreatorFunc> creators;
};
