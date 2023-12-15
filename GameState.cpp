// GameState.cpp
#include "GameState.hpp"
#include "InGame.hpp"
#include "MainMenu.hpp"
#include <SFML/Graphics.hpp>

// Implémentez les méthodes virtuelles pures ici
// Exemple pour MainMenu
void GameState::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    // Gestion des événements spécifiques au MainMenu
}

void GameState::update(sf::Time deltaTime, sf::RenderWindow& window)
{
    // Logique de mise à jour spécifique au MainMenu
}

void GameState::draw(sf::RenderWindow& window)
{
    // Dessinez les éléments spécifiques au MainMenu
}

GameState* GameState::getNextState()
{
    return nullptr;
}

bool GameState::isRunning()
{
    return true;
}
