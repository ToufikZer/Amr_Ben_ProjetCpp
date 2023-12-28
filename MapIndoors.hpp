#pragma once
#include "iostream"
#include "TileMap.hpp"
#include "NPC.hpp"
#include "SFML/Audio.hpp"
#include "Obstacle.hpp"

class MapIndoors {
public:
    MapIndoors() = default;
    MapIndoors(std::string MapName, std::string BackgroundPath, std::vector<NPC> NPCs,std::vector<Obstacle> obstacles, std::string MusicPath, unsigned int FloorNumber, float PlayerSpeed);
    MapIndoors(std::string MapName, std::string BackgroundPath, std::vector<Obstacle> obstacles, std::string MusicPath, unsigned int FloorNumber, float PlayerSpeed);
    MapIndoors(std::string MapName, std::string BackgroundPath, std::vector<NPC> NPCs, std::string MusicPath, unsigned int FloorNumber, float PlayerSpeed);
    MapIndoors(std::string MapName, std::string BackgroundPath, std::string MusicPath, unsigned int FloorNumber, float PlayerSpeed);

    std::string getBackgroundPath(){
        return BackgroundPath;
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

    std::string getName(){
        return MapName;
    }

    unsigned int getFloorNb(){
        return FloorNumber;
    }

    float getPlayerSpeed(){
        return PlayerSpeed;
    }


private:
    std::string BackgroundPath;
    std::vector<NPC> NPCs;
    std::vector<Obstacle> obstacles;
    std::string MusicPath;
    std::string MapName;
    unsigned int FloorNumber;
    float PlayerSpeed;
};
