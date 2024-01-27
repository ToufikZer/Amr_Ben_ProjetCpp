// InGame.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "MapManager.hpp"
#include "Map.hpp"
#include "Keybinds.hpp"
#include "Indoors.hpp"
#include "InGame_CarGameplay.hpp"
#include "Bagarre.hpp"
#include "FraudeGameplay.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Save.hpp"

class InGame : public GameState {
public:
    InGame(sf::RenderWindow& window);
    InGame(sf::RenderWindow& window, sf::Vector2u currentmap, sf::Vector2f pos_player, sf::Vector2u map_dimension, Inventory inventaire, unsigned int player_direction, std::string objectif_text);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState() ;

private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Text objectif;
    std::string objectif_text;
    MapManager maps;
    TileMap map;
    Player player;
    sf::Font font;
    sf::Music music;
    // sf::SoundBuffer buffer_bump;
    // sf::Sound bump_sound;
    std::string MusicPath;
    std::vector<std::vector<int>> level;     
    std::vector<NPC> NPCs;
    std::vector<Obstacle> obstacles;

    std::vector<std::string> first_dialogue;
    bool isTalking;
    NPC* npcThatWasTalking;
    unsigned int currentMessage;
    Obstacle* obstacleInteracting;
    bool in_house;
    bool labyrinthe;
    bool backmenu;

    void EnterHouseUp();
    void EnterHouseDown();

// FAIRE PAREIL POUR DISCUSSION AVEC A

    void initialize();
    void CheckChangeMap(sf::Vector2u position);

    void executeOption();

};
