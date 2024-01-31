#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "Explication.hpp"

class PseudoInterface : public GameState {
public:
    PseudoInterface(sf::RenderWindow& window, Save save);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState(); 

    std::string& getPseudo(){
        return pseudo;
    }

private:
    sf::RenderWindow& window;
    sf::RectangleShape Rectangle;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text text;
    sf::Text back;
    sf::Text ok;
    sf::Text pseudo_text;
    std::string pseudo;
    bool launch_game;
    bool can_launch;
    bool come_back;
    Save save;

    void initialize_menu();
    void initialize_pseudo();
    void Detect_OK(sf::RenderWindow& window);
    void Detect_Back(sf::RenderWindow& window);
    void HighlightOK();
    void ResetOK();
    void HighlightBack();
    void ResetBack();
};