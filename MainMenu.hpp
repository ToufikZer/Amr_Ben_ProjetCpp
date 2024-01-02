// MainMenu.hpp
#pragma once
#include "GameState.hpp"
#include "Save.hpp"
#include "Indoors.hpp"
#include "InGame.hpp"
#include "Keybinds.hpp"
#include "PseudoInterface.hpp"
#include <SFML/Graphics.hpp>

class MainMenu : public GameState {
public:
    MainMenu(sf::RenderWindow& window, Save save);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) ; 
    void update(sf::Time deltaTime, sf::RenderWindow& window) ;
    void draw(sf::RenderWindow& window, sf::Event& event) ;
    GameState* getNextState() ;
    bool isRunning();


private:
    Save save;
    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text titleText;
    sf::Text continueText;
    sf::Text startText;
    sf::Text exitText;
    sf::Text ctrlText;

    int selectedOption;
    bool start_game;                // dit si on doit entrer dans InGame
    bool keybinds;                  // dit si on doit entrer dans les controles de keybind
    bool keyboard_pressed;          // permet de verifier si le clavier a été pressé pour figer la sélection dans le menu sinon ca highlight que pendant une frame

    void Detect_Continue(sf::RenderWindow& window);
    void Detect_Start(sf::RenderWindow& window);
    void Detect_Exit(sf::RenderWindow& window);
    void Detect_Ctrl(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    void executeOption();
    void HighlightContinue();
    void ResetContinue();
    void HighlightStart();
    void ResetStart();
    void HighlightCtrl();
    void ResetCtrl();
    void HighlightExit();
    void ResetExit();

    bool continue_game;
};
