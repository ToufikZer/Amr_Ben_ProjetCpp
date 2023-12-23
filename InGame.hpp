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

class InGame : public GameState {
public:
    InGame(sf::RenderWindow& window, sf::Vector2u currentmap, sf::Vector2u pos_player, sf::Vector2u map_dimension, unsigned int player_direction);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
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
    MapManager maps;

    bool backmenu;
    bool escape_menu = false;
    bool in_house;
    bool isTalking;
    NPC* npcThatWasTalking;
    Obstacle* obstacleInteracting;
    int currentMessage;


    sf::RectangleShape back_menu;
    sf::Text question;
    sf::Text yesText;
    sf::Text cancelText;
    sf::RectangleShape line;

    void initialize();
    void CheckChangeMap(sf::Vector2u position);
    void drawConfirmationWindow(sf::RenderWindow& window);

    void HighlightCancel();
    void ResetCancel();
    void HighlightYes();
    void ResetYes();

    void Detect_Yes(sf::RenderWindow& window);
    void Detect_Cancel(sf::RenderWindow& window);
};
