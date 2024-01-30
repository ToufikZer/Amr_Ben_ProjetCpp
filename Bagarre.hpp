// Bagarre.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.hpp"
#include "PlayerBagarre.hpp"
#include "Projectile.hpp"
#include "EnnemiBagarre.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "MapManager.hpp"
#include "Map.hpp"
#include "MiniJeu.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

class Bagarre : public GameState {
public:
    Bagarre(sf::RenderWindow& window, Save save, Inventory inventaire, std::string backgroundPath, float ennemi_attack_speed, unsigned int ennemi_degats, int attack_delay, int HP, int id_bagarre);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState() ;

private:
    sf::RenderWindow& window;
    sf::Time elapsed; 
    sf::View view;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    PlayerBagarre player;
    EnnemiBagarre ennemi;
    sf::Music music;
    std::string MusicPath;
    std::vector<Obstacle> obstacles;
    std::vector<Projectile> projs_player;

    sf::RectangleShape playerHealthBar;
    sf::RectangleShape ennemiHealthBar;
    sf::Text Finish;
    sf::Text Lose;
    bool backmenu;
    Save save;
    bool combat_lose;
    bool combat_win;
    int id_bagarre;
};