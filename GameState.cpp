// GameState.cpp
#include "GameState.hpp"
#include "InGame.hpp"
#include "MainMenu.hpp"
#include <SFML/Graphics.hpp>

void GameState::handleEvent(sf::Event& event, sf::RenderWindow& window)
{

}

void GameState::update(sf::Time deltaTime, sf::RenderWindow& window)
{

}

void GameState::draw(sf::RenderWindow& window)
{

}

GameState* GameState::getNextState()
{
    return nullptr;
}

bool GameState::isRunning()
{
    return true;
}
