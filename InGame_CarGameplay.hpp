// InGame_CarGameplay.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.hpp"
#include "PlayerCar.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "MapManager.hpp"
#include "Map.hpp"
#include "MiniJeu.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

class InGame_CarGameplay : public GameState {
public:
    InGame_CarGameplay(sf::RenderWindow& window, Save save, Inventory inventaire, bool minijeu);

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
    PlayerCar player;
    sf::Music music;
    std::string MusicPath;
    std::vector<std::vector<int>> level;     
    std::vector<Obstacle> obstacles;

    sf::Text Finish;
    bool backmenu;
    Save save;
    bool is_arrived;
    bool minijeu;
};