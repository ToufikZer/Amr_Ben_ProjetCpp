// Player.cpp
#include "PlayerBagarre.hpp"

#include "TileMap.hpp"
#include "Obstacle.hpp"
#include "Projectile.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

bool last_moveB = true; //true si dernier deplacement à droite, false sinon


PlayerBagarre::PlayerBagarre(const std::string &texturePath, float pos_x, float pos_y, Inventory inventaire):
    inventaire(inventaire),
    speed(150)
    {

    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
        std::exit(-1);
    }
    
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(m_texture.getSize().x/4, 0.f);
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x/4, m_texture.getSize().y/2);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y/2);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x/4, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x/4, m_texture.getSize().y/2);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y/2);

    m_vertices[0].color = sf::Color::White;
    m_vertices[1].color = sf::Color::White;
    m_vertices[2].color = sf::Color::White;
    m_vertices[3].color = sf::Color::White;

    setPosition(pos_x, pos_y);
}

void PlayerBagarre::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}


Projectile PlayerBagarre::tir(unsigned int degats, float vitesse, sf::Vector2f position, std::string direction){
    return Projectile(vitesse, degats, position, direction, "texture/texture_obstacle/proj.png", 1);
}


void PlayerBagarre::update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, 
                           sf::View& view, std::vector<Obstacle> obstacles){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if(!out_map(map_width, map_height, sf::Vector2f(getPosition().x + speed* deltaTime.asSeconds(), getPosition().y))){
                    //if(!collision_obstacles(sf::Vector2f(sf::Vector2f(getPosition().x + speed* deltaTime.asSeconds(), getPosition().y)),obstacles)){
                        move(speed * deltaTime.asSeconds(), 0.f);
                        update_texture(0, (int)getPosition().x / 10 % 4);
                        last_moveB = true;
                    //}
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                if(!out_map(map_width, map_height, sf::Vector2f(getPosition().x - speed* deltaTime.asSeconds(), getPosition().y))){
                    //if(!collision_obstacles(sf::Vector2f(sf::Vector2f(getPosition().x - speed* deltaTime.asSeconds(), getPosition().y)),obstacles)){
                        move(-speed * deltaTime.asSeconds(), 0.f);
                        update_texture(1, (int)getPosition().x / 10 % 4);
                        last_moveB = false;
                    //}
                }
            }
            else {
                if(last_moveB)
                    update_texture(0, 0);
                else{
                    update_texture(1,0);
                }
            }
}

void PlayerBagarre::update_texture(unsigned int u, unsigned int i) {
    m_vertices[0].texCoords = sf::Vector2f((i) * m_texture.getSize().x/4, (u) * m_texture.getSize().y/2);
    m_vertices[1].texCoords = sf::Vector2f((i+1) * m_texture.getSize().x/4, (u) * m_texture.getSize().y/2);
    m_vertices[2].texCoords = sf::Vector2f((i+1) * m_texture.getSize().x/4, (u+1) * m_texture.getSize().y/2);
    m_vertices[3].texCoords = sf::Vector2f((i) * m_texture.getSize().x/4, (u+1) * m_texture.getSize().y/2);
}

bool PlayerBagarre::out_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position) {
    if (position.x >= map_width - m_texture.getSize().x /4 || position.x < 0.f)
        return true;
    return false;
}

void PlayerBagarre::drawInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view){
    inventaire.displayInventory(window, font, view);
}

// void PlayerBagarre::drawInteractText(sf::RenderWindow& window, sf::Font& font){
//     InteractText.setFont(font);
//     window.draw(InteractText);
// }