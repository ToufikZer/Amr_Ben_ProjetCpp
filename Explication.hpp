#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "Inventory.hpp"
#include "Save.hpp"


class Explication : public GameState {
public:
    Explication(sf::RenderWindow& window, std::string name, Save save, std::string backgroundPath);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState() ;

private:
    sf::RenderWindow& window;
    sf::Time elapsed; 
    sf::View view;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music music;
    std::string MusicPath;

    bool backmenu;
    bool expl;
    std::string name;
    Save save;
};
