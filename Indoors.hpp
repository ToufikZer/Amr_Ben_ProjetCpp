// InGame_CarGameplay.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "PlayerIndoors.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "MapIndoors.hpp"
#include "InGame.hpp"
#include "Item.hpp"

class Indoors : public GameState {
public:
    Indoors(sf::RenderWindow& window, std::string MapName, float pos_player_x, float pos_player_y, Inventory inventaire);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    GameState* getNextState() ;

private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    MapIndoors map;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music music;
    std::string BackgroundPath;
    std::string MusicPath;  
    std::vector<Obstacle> obstacles;
    std::vector<NPC> NPCs;
    unsigned int FloorNumber;
    float PlayerSpeed;
    PlayerInDoors player;
    std::vector<MapIndoors> MapList;

    bool isTalking;
    NPC* npcThatWasTalking;
    int currentMessage;

    bool back_to_town;
    bool next_town;
    bool kitchen;
    bool crous;

    bool has_key(Inventory inventaire);
    bool has_kitchen_knife(Inventory inventaire);
};