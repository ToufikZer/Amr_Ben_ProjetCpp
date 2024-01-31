// Fraudeur.hpp
#pragma once

#include "Obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
class Fraudeur : public sf::Drawable, public sf::Transformable {
public:
    Fraudeur(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y, Inventory inventaire);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<Obstacle> obstacles);

    void update_texture(unsigned int u);

    void draw_crash(sf::RenderWindow& window);

    void setSpeed(float value){
        speed = value;
    }

    bool getCrash(){
        return crash;
    }

    void setCrash(bool value){
        crash = value;
    }

    Inventory getInventory() const {
        return inventaire;
    }

    void drawInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view);

private:
    void initialize_crash();
    bool collision_obstacles(sf::Vector2f position, std::vector<Obstacle> obstacles);
    bool in_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position);
    void sauter();
    void sauter_anim();
    void courir_anim();
    void deplacer_vert();
    void deplacer_horiz(unsigned int map_width, unsigned int map_height);

    sf::Time elapsed; 
    sf::Texture m_texture;
    sf::VertexArray m_vertices;

    bool crash;
    float speed;
    bool invincible;
    Inventory inventaire;
    sf::Text CrashText;

};
