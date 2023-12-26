#pragma once
#include "iostream"
#include "TileMap.hpp"
#include "NPC.hpp"
#include "SFML/Audio.hpp"
#include "Obstacle.hpp"

class MapIndoors {
public:
    MapIndoors() = default;
    MapIndoors(std::string BackgroundPath, std::vector<NPC> NPCs,std::vector<Obstacle> obstacles, std::string MusicPath);
    MapIndoors(std::string BackgroundPath, std::vector<Obstacle> obstacles, std::string MusicPath);
    MapIndoors(std::string BackgroundPath, std::vector<NPC> NPCs, std::string MusicPath);
    MapIndoors(std::string BackgroundPath, std::string MusicPath);

private:

};
