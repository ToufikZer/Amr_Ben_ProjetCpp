#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "InGame.hpp"
#include "InGame_CarGameplay.hpp"
#include "MainMenu.hpp"

class PseudoInterface : public GameState {
public:
    PseudoInterface(sf::RenderWindow& window);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    GameState* getNextState(); 

    std::string& getPseudo(){
        return pseudo;
    }

private:
    sf::RectangleShape blueRectangle;
    sf::RectangleShape blueRectangleTop;
    sf::RectangleShape blueRectangleLeft;
    sf::RectangleShape blueRectangleRight;
    sf::RectangleShape blueRectangleBot;
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text text;
    sf::Text back;
    sf::Text ok;
    sf::Text pseudo_text;
    std::string pseudo;
    bool can_launch;
    bool launch_game;
    bool come_back;

    void Detect_OK(sf::RenderWindow& window);
    void Detect_Back(sf::RenderWindow& window);
    void HighlightOK();
    void ResetOK();
    void HighlightBack();
    void ResetBack();
};