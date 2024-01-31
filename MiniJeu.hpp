// MiniJeu.hpp
#pragma once
#include "GameState.hpp"
#include "Save.hpp"
#include "Indoors.hpp"
#include "InGame.hpp"
#include "Labyrinthe.hpp"
#include "MiniJeu.hpp"
#include "PseudoInterface.hpp"
#include <SFML/Graphics.hpp>

class MiniJeu : public GameState {
public:
    MiniJeu(sf::RenderWindow& window, Save save);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) ; 
    void update(sf::Time deltaTime, sf::RenderWindow& window) ;
    void draw(sf::RenderWindow& window, sf::Event& event) ;
    GameState* getNextState() ;


private:
    void initialize_text();

    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text titleText;
    sf::Text carText;
    sf::Text fraudeText;
    sf::Text exitText;
    sf::Text bagarreText;

    int selectedOption;
    bool bagarre_game;
    bool car_game;               
    bool fraude_game;               
    bool keyboard_pressed;          

    Save save;

    void Detect_Car(sf::RenderWindow& window);
    void Detect_Fraude(sf::RenderWindow& window);
    void Detect_Exit(sf::RenderWindow& window);
    void Detect_Bagarre(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    void executeOption();
    void HighlightCar();
    void ResetCar();
    void HighlightFraude();
    void ResetFraude();
    void HighlightBagarre();
    void ResetBagarre();
    void HighlightExit();
    void ResetExit();
};