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
#include "Keybinds.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

class Bagarre : public GameState {
public:
    Bagarre(sf::RenderWindow& window, Save save, Inventory inventaire, std::string backgroundPath);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState() ;

private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    PlayerBagarre player;
    EnnemiBagarre ennemi;
    sf::Music music;
    std::string MusicPath;
    std::vector<Obstacle> obstacles;
    std::vector<Projectile> projs;

    sf::Text Finish;
    bool backmenu;
    Save save;
    bool is_arrived;
};