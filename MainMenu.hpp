// MainMenu.hpp
#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class MainMenu : public GameState {
public:
    MainMenu(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) ; 
    void Detect_Start(sf::RenderWindow& window);
    void Detect_Exit(sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window) ;
    void draw(sf::RenderWindow& window) ;
    GameState* getNextState() ;
    bool isRunning();


private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text titleText;
    sf::Text startText;
    sf::Text exitText;
    int selectedOption;
    bool start_game;

    void moveUp();
    void moveDown();
    void executeOption();
};
