#pragma once
#include "iostream"
#include "TileMap.hpp"
#include "NPC.hpp"
#include "SFML/Audio.hpp"
#include "Obstacle.hpp"

class Map {
public:
    Map() = default;
    Map(std::vector<std::vector<int>> level, std::vector<NPC> NPCs,std::vector<Obstacle> obstacles, std::string MusicPath);
    Map(std::vector<std::vector<int>> level, std::vector<Obstacle> obstacles, std::string MusicPath);
    Map(std::vector<std::vector<int>> level, std::vector<NPC> NPCs, std::string MusicPath);
    Map(std::vector<std::vector<int>> level, std::string MusicPath);
    
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

    std::string getMusicPath(){
        return MusicPath;
    }



private:
    std::vector<std::vector<int>> level;
    std::vector<NPC> NPCs;
    std::vector<Obstacle> obstacles;
    std::string MusicPath;
};