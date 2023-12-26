// InGame_CarGameplay.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.hpp"
#include "PlayerIndoors.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "MapManager.hpp"
#include "Map.hpp"
#include "Keybinds.hpp"

class Indoors : public GameState {
public:
    Indoors(sf::RenderWindow& window);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    GameState* getNextState() ;

private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music music;
    std::string MusicPath;  
    PlayerInDoors player;
    std::vector<Obstacle> obstacles;

};