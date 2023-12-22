#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "MainMenu.hpp"
class Keybinds : public GameState {
public:
    Keybinds(sf::RenderWindow& window);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    GameState* getNextState(); 

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text text;
    sf::Text back;

    bool come_back;
    void Detect_Back(sf::RenderWindow& window);
    void HighlightBack();
    void ResetBack();
};