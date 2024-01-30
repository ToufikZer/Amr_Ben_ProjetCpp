// FraudeGameplay.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.hpp"
#include "Fraudeur.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "MapManager.hpp"
#include "Map.hpp"
#include "MiniJeu.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

class FraudeGameplay : public GameState {
public:
    FraudeGameplay(sf::RenderWindow& window, Save save, Inventory inventaire);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState() ;

private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music music;
    std::string MusicPath;
    TileMap map;
    std::vector<std::vector<int>> level;     
    Fraudeur player;
    std::vector<Obstacle> obstacles;

    sf::Text Finish;
    bool backmenu;
    Save save;
    bool is_arrived;
};