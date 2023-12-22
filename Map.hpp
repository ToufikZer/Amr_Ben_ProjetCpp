#pragma once
#include "iostream"
#include "TileMap.hpp"
#include "NPC.hpp"
#include "SFML/Audio.hpp"
#include "Obstacle.hpp"

class Map {
public:
    Map() = default;
    Map(std::vector<std::vector<int>> level, std::vector<NPC> NPCs,std::vector<Obstacle> obstacles, std::vector<sf::Vector2u> ChangeTile, std::string MusicPath);
    // une methode par map qui set la valeur de level, dimension et npc
    std::vector<std::vector<int>> getLevel() const
    {
        return level;
    }

    std::vector<NPC> const& getNPCs() const
    {
        return NPCs;
    }

    std::vector<Obstacle> const& getObstacles() const
    {
        return obstacles;
    }

    std::vector<sf::Vector2u> const& getChangeTile() const
    {
        return ChangeTile;
    }

    std::string getMusicPath(){
        return MusicPath;
    }



private:
    std::vector<std::vector<int>> level;
    std::vector<NPC> NPCs;
    std::vector<Obstacle> obstacles;
    std::vector<sf::Vector2u> ChangeTile;
    std::string MusicPath;
};
// extern Map map3;