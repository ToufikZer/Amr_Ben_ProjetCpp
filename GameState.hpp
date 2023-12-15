// GameState.hpp
#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:
    void handleEvent(sf::Event& event, sf::RenderWindow& window) ;
    void update(sf::Time deltaTime, sf::RenderWindow& window) ;
    void draw(sf::RenderWindow& window, sf::Font& font) ;
    GameState* getNextState() ;
    bool isRunning() ;
};