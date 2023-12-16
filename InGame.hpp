// InGame.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "GameState.hpp"
#include "MapManager.hpp"

class InGame : public GameState {
public:
    InGame(sf::RenderWindow& window);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    TileMap map;
    std::vector<std::vector<int>> level;     
    Player player;
    std::vector<NPC> NPCs;
    MapManager maps;

    bool isTalking;
    NPC* npcThatWasTalking;
    int currentMessage;

    void initialize();
    void CheckChangeMap(sf::Vector2u position);
};
