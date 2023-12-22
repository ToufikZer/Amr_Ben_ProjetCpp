#include "iostream"
#include "Map.hpp"
#include <SFML/Audio.hpp>

Map::Map(std::vector<std::vector<int>> level, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles, std::vector<sf::Vector2u> ChangeTile, std::string MusicPath) :
    level(level),
    NPCs(NPCs),
    obstacles(obstacles),
    ChangeTile(ChangeTile),
    MusicPath(MusicPath)
    {
    // if (!music.openFromFile(MusicPath)){ 
    //     std::cerr << "Erreur lors du chargement du son" << std::endl;
    //     std::exit(-1);
    // }
    // music.setVolume(1);
    // music.setLoop(true);
    // music.play();  
}