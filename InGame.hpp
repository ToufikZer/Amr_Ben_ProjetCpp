// InGame.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "GameState.hpp"

class InGame : public GameState {
public:
    InGame(sf::RenderWindow& window);

    void handleInput();
    void update(sf::Time deltaTime);
    void draw();

private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    TileMap map;
    Player player;
    std::vector<NPC> NPCs;

    bool isTalking;
    NPC* npcThatWasTalking;
    int currentMessage;

    void initialize();
};
