// GameState.hpp
#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:
    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) ;
    virtual void update(sf::Time deltaTime, sf::RenderWindow& window) ;
    virtual void draw(sf::RenderWindow& window, sf::Event& event) ;
    virtual GameState* getNextState() ;
    virtual bool isRunning();
    virtual ~GameState() {}
};