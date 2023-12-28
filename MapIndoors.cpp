#include "MapIndoors.hpp"

    MapIndoors::MapIndoors(std::string MapName, std::string BackgroundPath, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles, std::string MusicPath, unsigned int FloorNumber, float PlayerSpeed) :
    MapName(MapName),
    BackgroundPath(BackgroundPath),
    NPCs(NPCs),
    obstacles(obstacles),
    MusicPath(MusicPath),
    FloorNumber(FloorNumber),
    PlayerSpeed(PlayerSpeed)
    {

}

    MapIndoors::MapIndoors(std::string MapName, std::string BackgroundPath, std::vector<Obstacle> obstacles, std::string MusicPath, unsigned int FloorNumber, float PlayerSpeed) :
        MapName(MapName),
        BackgroundPath(BackgroundPath),
        obstacles(obstacles),
        MusicPath(MusicPath),
        FloorNumber(FloorNumber),
        PlayerSpeed(PlayerSpeed)
        {
            
    }

    MapIndoors::MapIndoors(std::string MapName, std::string BackgroundPath, std::vector<NPC> NPCs, std::string MusicPath, unsigned int FloorNumber, float PlayerSpeed) :
        MapName(MapName),
        BackgroundPath(BackgroundPath),
        NPCs(NPCs),
        MusicPath(MusicPath),
        FloorNumber(FloorNumber),
        PlayerSpeed(PlayerSpeed)
        {
            
    }

    MapIndoors::MapIndoors(std::string MapName, std::string BackgroundPath, std::string MusicPath, unsigned int FloorNumber, float PlayerSpeed) :
        MapName(MapName),
        BackgroundPath(BackgroundPath),
        MusicPath(MusicPath),
        FloorNumber(FloorNumber),
        PlayerSpeed(PlayerSpeed)
        {
            
    }