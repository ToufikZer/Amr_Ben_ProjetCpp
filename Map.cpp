#include "iostream"
#include "Map.hpp"
#include <SFML/Audio.hpp>

Map::Map(std::vector<std::vector<int>> level, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles, std::string MusicPath) :
    level(level),
    NPCs(NPCs),
    obstacles(obstacles),
    MusicPath(MusicPath)
    {

}

Map::Map(std::vector<std::vector<int>> level, std::vector<Obstacle> obstacles, std::string MusicPath) :
    level(level),
    obstacles(obstacles),
    MusicPath(MusicPath)
    {
        
}

Map::Map(std::vector<std::vector<int>> level, std::vector<NPC> NPCs, std::string MusicPath) :
    level(level),
    NPCs(NPCs),
    MusicPath(MusicPath)
    {
        
}

Map::Map(std::vector<std::vector<int>> level, std::string MusicPath) :
    level(level),
    MusicPath(MusicPath)
    {
        
}