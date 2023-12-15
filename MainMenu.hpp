// MainMenu.hpp
#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class MainMenu : public GameState {
public:
    MainMenu(sf::RenderWindow& window);
    void handleEvent() ; 
    void handleInput() ;
    void update() ;
    void draw(sf::RenderWindow& window) ;
    GameState* getNextState() ;
    bool isRunning();


private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text exitText;
    int selectedOption;

    void moveUp();
    void moveDown();
    void executeOption();
};
