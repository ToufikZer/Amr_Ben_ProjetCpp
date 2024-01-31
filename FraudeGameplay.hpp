// FraudeGameplay.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "GameState.hpp"
#include "TileMap.hpp"
#include "Fraudeur.hpp"
#include "Obstacle.hpp"
#include "MainMenu.hpp"
#include "MiniJeu.hpp"
#include "Inventory.hpp"

class FraudeGameplay : public GameState {
public:
    FraudeGameplay(sf::RenderWindow& window, Save save, Inventory inventaire, bool minijeu);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState() ;

private:
    void initialize_obstacles();
    void initialize_finish();

    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    TileMap map;
    std::vector<std::vector<int>> level;     
    Fraudeur player;
    std::vector<Obstacle> obstacles;

    sf::Text Finish;
    bool backmenu;
    Save save;
    bool is_arrived;
    bool minijeu;
};