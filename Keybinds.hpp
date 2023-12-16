#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "GameState.hpp"
#include "MapManager.hpp"

class Keybinds : public GameState {
public:
    Keybinds(sf::RenderWindow& window);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text text;
};