// PlayerBagarre.hpp
#pragma once

#include "TileMap.hpp"
#include "Obstacle.hpp"
#include "NPC.hpp"
#include "CharacterBagarre.hpp"
#include "Inventory.hpp"
#include "Projectile.hpp"
#include "Item.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

class PlayerBagarre : public sf::Drawable, public sf::Transformable{
public:
    PlayerBagarre(const std::string& texturePath, float pos_x, float pos_y, Inventory inventaire);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, sf::View& view, 
                std::vector<Obstacle> obstacles);

    void update_texture(unsigned int u, unsigned int i);

    bool collision(Projectile& proj);

    sf::FloatRect getGlobalBounds() const {
        return getTransform().transformRect(m_vertices.getBounds());
    }

    Projectile tir(unsigned int degats, float vitesse, sf::Vector2f position, std::string direction = "haut");

    Inventory& getInventory(){
        return inventaire;
    }
    
    void drawInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view);
    // void drawInteractText(sf::RenderWindow& window, sf::Font& font);
protected:
    bool out_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position);

private:
    // sf::Text InteractText;
    sf::Time elapsed; 
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    Inventory inventaire;
    float speed;
    int HP = 100;
};
