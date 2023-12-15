#pragma once
#include "GameState.hpp"
#include "NPC.hpp"
#include <SFML/Graphics.hpp>

class Conversation : public GameState {
public:
    Conversation(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    GameState* getNextState() ;
    bool isRunning();


private:
    sf::RenderWindow& window;
    NPC npc_talking;
    sf::Font font;
    sf::RectangleShape Rectangle;
    sf::RectangleShape RectangleTop;
    sf::RectangleShape RectangleLeft;
    sf::RectangleShape RectangleRight;
    sf::RectangleShape RectangleBot;
    sf::Text message;
    std::vector<std::string> dialogue;
    int current_message;
};
