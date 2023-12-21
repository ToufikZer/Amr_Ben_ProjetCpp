#pragma once
#include "iostream"
#include "TileMap.hpp"
#include "NPC.hpp"
#include "SFML/Audio.hpp"
#include "Map.hpp"

class MapManager{
    public:
    MapManager();
    // ~MapManager();

    std::vector<std::vector<Map>> getMapMap(){
        return MapMap;
    }

    sf::Vector2u getCurrentMap(){
        return current_map;
    }

    void setNextCurrentMap(){
        current_map.y += 1;
    }

    void setPreviousCurrentMap(){
        current_map.y -= 1;
    }

    void setUpCurrentMap(){
        current_map.x -= 1;
    }

    void setDownCurrentMap(){
        current_map.x += 1;
    }
private:
    std::vector<std::vector<Map>> MapMap;
    sf::Vector2u current_map;
};