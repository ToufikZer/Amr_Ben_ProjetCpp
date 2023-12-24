// MainMenu.hpp
#pragma once
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class MainMenu : public GameState {
public:
    MainMenu(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) ; 
    void update(sf::Time deltaTime, sf::RenderWindow& window) ;
    void draw(sf::RenderWindow& window) ;
    GameState* getNextState() ;
    bool isRunning();


private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text titleText;
    sf::Text startText;
    sf::Text exitText;
    sf::Text ctrlText;

    int selectedOption;
    bool start_game;                // dit si on doit entrer dans InGame
    bool keybinds;                  // dit si on doit entrer dans les controles de keybind
    bool keyboard_pressed;          // permet de verifier si le clavier a été pressé pour figer la sélection dans le menu sinon ca highlight que pendant une frame

    void Detect_Start(sf::RenderWindow& window);
    void Detect_Exit(sf::RenderWindow& window);
    void Detect_Ctrl(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    void executeOption();
    void HighlightStart();
    void ResetStart();
    void HighlightCtrl();
    void ResetCtrl();
    void HighlightExit();
    void ResetExit();
};
