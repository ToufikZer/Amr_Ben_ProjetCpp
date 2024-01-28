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

    sf::FloatRect getHitbox() const {
    sf::FloatRect originalBounds = getTransform().transformRect(m_vertices.getBounds());

    sf::FloatRect reducedBounds(
        originalBounds.left + 17.f,
        originalBounds.top + 6.f,
        originalBounds.width /3,
        originalBounds.height - 6.f
    );

    return reducedBounds;
}


    Projectile tir(unsigned int degats, float vitesse, sf::Vector2f position, std::string direction = "haut");

    bool has_knife();

    Inventory& getInventory(){
        return inventaire;
    }
    
    int getHP(){
        return HP;
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
    int HP;
};
