// InGame_CarGameplay.hpp
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
    InGame(sf::RenderWindow& window);

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
    std::vector<Obstacle> obstacles;
};