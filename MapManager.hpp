#pragma once
#include "iostream"
#include "TileMap.hpp"
#include "NPC.hpp"

class MapManager {
public:
    // une methode par map qui set la valeur de level, dimension et npc
    std::vector<std::vector<int>> const& getLevel() const
    {
        return level;
    }
    std::vector<NPC> const& getNPCs() const
    {
        return NPCs;
    }
    void setMap_map1();

    void setMap_map2();

private:
    std::vector<std::vector<int>> level;
    std::vector<NPC> NPCs;
};