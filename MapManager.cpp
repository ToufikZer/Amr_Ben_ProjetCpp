#include "iostream"
#include "MapManager.hpp"
#include <SFML/Audio.hpp>



void MapManager::setMap_map1(){
    //std::cout << "ok" << std::endl;
    if (!music.openFromFile("sound/music/music1.ogg")){
        std::cerr << "Erreur lors du chargement du son" << std::endl;
        std::exit(-1);
    }
    music.setVolume(0.5);
    music.play();
        level  = 
        {{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
        {0,1,1,1,1,1,1,0,0,0,0,2,0,0,0,0},
        {1,1,0,0,0,0,0,0,3,3,3,3,3,3,3,3},
        {0,1,0,0,2,3,3,3,3,0,1,1,1,0,0,0}, // modem limeaire idéoriginel
        {0,1,1,0,3,3,3,0,0,0,1,1,1,2,0,0},
        {0,0,1,0,3,0,2,2,0,0,1,1,1,1,2,0},
        {2,0,1,0,3,0,2,2,2,0,1,1,1,1,1,1},
        {0,0,1,0,3,2,2,2,0,0,0,0,1,1,1,1},
        {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
        {2,1,1,1,1,0,1,0,0,0,0,2,0,0,0,0},
        {1,1,0,0,0,0,0,0,3,3,3,3,3,3,3,3},
        {0,1,0,0,2,0,3,3,3,0,1,1,1,0,0,0},
        {0,1,1,0,3,3,3,0,0,0,1,1,1,2,0,0},
        {0,0,1,0,3,0,2,2,0,0,1,1,1,1,2,0},
        {2,0,1,0,3,0,2,2,2,0,1,1,1,1,1,1},
        {0,0,1,0,3,2,2,2,0,0,0,0,1,1,1,1}};

    NPCs.clear();
    NPCs.push_back(NPC("texture/texture_npc/npcpkmn.png", 8, 13, {"Salut", "test", "caca"},"RULD"));
    NPCs.push_back(NPC("texture/texture_npc/npcpkmn.png", 0, 8, {"Salut2", "pioupiou", "hello!"},"RRRUUUDDDLLL"));

    ChangeTile.clear();
    ChangeTile.push_back({sf::Vector2u(0,7)});
    }

    void MapManager::setMap_map2(){
        if (!music.openFromFile("sound/music/music2.ogg")){
            std::cerr << "Erreur lors du chargement du son" << std::endl;
            std::exit(-1);
        }
        music.setVolume(0.5);
        music.play();
        level  = 
        {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0},
        {0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3},
        {0,0,0,0,2,3,3,3,3,0,0,0,0,0,0,0}, // modem limeaire idéoriginel
        {0,0,0,0,3,3,3,0,0,0,0,0,0,2,0,0},
        {0,0,0,0,3,0,2,2,0,0,0,0,0,0,2,0},
        {2,0,0,0,3,0,2,2,2,0,0,0,0,0,0,0},
        {0,0,0,0,3,2,2,2,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0},
        {0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3},
        {0,0,0,0,2,0,3,3,3,0,0,0,0,0,0,0},
        {0,0,0,0,3,3,3,0,0,0,0,0,0,2,0,0},
        {0,0,0,0,3,0,2,2,0,0,0,0,0,0,2,0},
        {2,0,0,0,3,0,2,2,2,0,0,0,0,0,0,0},
        {0,0,0,0,3,2,2,2,0,0,0,0,0,0,0,0}};
    NPCs.clear();
    NPCs.push_back(NPC("texture/texture_npc/npcpkmn.png", 9, 9, {"Salut", "test", "caca"},"RULD"));
    NPCs.push_back(NPC("texture/texture_npc/npcpkmn.png", 0, 3, {"Salut2", "pioupiou", "hello!"},"RULD"));
    
    ChangeTile.clear();
    ChangeTile.push_back(sf::Vector2u(7,4));
    }