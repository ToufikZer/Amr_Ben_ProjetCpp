// Bagarre.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "GameState.hpp"
#include "PlayerBagarre.hpp"
#include "EnnemiBagarre.hpp"
#include "Projectile.hpp"
#include "MainMenu.hpp"
#include "MiniJeu.hpp"
#include "Inventory.hpp"

class Bagarre : public GameState {
public:
    Bagarre(sf::RenderWindow& window, Save save, Inventory inventaire, std::string backgroundPath, std::string ennemiTexturePath, float ennemi_attack_speed, unsigned int ennemi_degats, int attack_delay, int HP, int id_bagarre, bool minijeu);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState() ;

private:
    void initialize_finish();
    void initialize_lose();

    sf::RenderWindow& window;
    sf::Time elapsed; 
    sf::View view;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    PlayerBagarre player;
    EnnemiBagarre ennemi;
    std::vector<Projectile> projs_player;

    sf::RectangleShape playerHealthBar;
    sf::RectangleShape ennemiHealthBar;
    sf::Text Finish;
    sf::RectangleShape rectFinish;
    sf::Text Lose;
    sf::RectangleShape rectLose;

    Save save;
    bool backmenu;
    bool combat_lose;
    bool combat_win;
    int id_bagarre;
    bool minijeu;
};