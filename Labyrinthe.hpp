// Labyrinthe.hpp
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
#include "MapInstances.hpp"
#include "Map.hpp"
#include "MiniJeu.hpp"
#include "Indoors.hpp"
#include "InGame_CarGameplay.hpp"
#include "FraudeGameplay.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Save.hpp"

class Labyrinthe : public GameState {
public:
    Labyrinthe(sf::RenderWindow& window);
    Labyrinthe(sf::RenderWindow& window, unsigned int nb_pas, sf::Vector2f pos_player, sf::Vector2u map_dimension, Inventory inventaire, unsigned int player_direction);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState() ;

private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    sf::Music music;
    std::string MusicPath;
    TileMap map;
    std::vector<std::vector<int>> level;     
    Player player;
    std::vector<NPC> NPCs;
    std::vector<Obstacle> obstacles;

    std::vector<std::string> first_dialogue;
    unsigned int nb_pas;
    bool light_off;
    bool isTalking;
    NPC* npcThatWasTalking;
    unsigned int currentMessage;
    bool end_lab;
    bool backmenu;

    void initialize();
    sf::Vector2u tp(sf::Vector2u tp_tile);

};
