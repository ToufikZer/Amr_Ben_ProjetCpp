// Player.cpp
#include "PlayerIndoors.hpp"

#include "TileMap.hpp"
#include "Obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

PlayerInDoors::PlayerInDoors(const std::string &texturePath, float pos_x, float pos_y, Inventory inventaire)
    {

    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
        std::exit(-1);
    }
    
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(m_texture.getSize().x /3, 0.f);
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x/3, m_texture.getSize().y);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x/3, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x/3, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].color = sf::Color::White;
    m_vertices[1].color = sf::Color::White;
    m_vertices[2].color = sf::Color::White;
    m_vertices[3].color = sf::Color::White;

    setPosition(pos_x, pos_y);
}

void PlayerInDoors::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

bool PlayerInDoors::collision_obstacles(sf::Vector2f position, std::vector<Obstacle> obstacles){
    for (Obstacle& obstacle : obstacles){
        if (sf::FloatRect(sf::Vector2f(position.x, position.y),sf::Vector2f(m_texture.getSize().x/3, m_texture.getSize().y)).intersects(obstacle.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

bool PlayerInDoors::collision_NPCs(sf::Vector2f position, NPC npc){
    if (sf::FloatRect(sf::Vector2f(position.x, position.y),sf::Vector2f(m_texture.getSize().x/3, m_texture.getSize().y)).intersects(npc.getGlobalBounds()))
    {
        return true;
    }
    return false;
}


void PlayerInDoors::update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, 
                           sf::View& view, std::vector<Obstacle> obstacles, std::vector<NPC> NPCs, unsigned int FloorNumber, bool is_talking){
        if (!is_talking){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                out_map(map_width, map_height, sf::Vector2f(getPosition().x + speed* deltaTime.asSeconds(), getPosition().y), FloorNumber);
                if(!collision_obstacles(sf::Vector2f(sf::Vector2f(getPosition().x + speed* deltaTime.asSeconds(), getPosition().y)),obstacles)){
                    move(speed * deltaTime.asSeconds(), 0.f);
                    update_texture(0);
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                out_map(map_width, map_height, sf::Vector2f(getPosition().x - speed* deltaTime.asSeconds(), getPosition().y), FloorNumber);
                if(!collision_obstacles(sf::Vector2f(sf::Vector2f(getPosition().x - speed* deltaTime.asSeconds(), getPosition().y)),obstacles)){
                    move(-speed * deltaTime.asSeconds(), 0.f);
                    update_texture(2);
                }
            }
            else {
                update_texture(1);
            }
        }
}

void PlayerInDoors::update_texture(unsigned int u) {
    m_vertices[0].texCoords = sf::Vector2f(u * m_texture.getSize().x/3, 0.f);
    m_vertices[1].texCoords = sf::Vector2f((u+1) * m_texture.getSize().x/3, 0.f);
    m_vertices[2].texCoords = sf::Vector2f((u+1) * m_texture.getSize().x/3, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(u * m_texture.getSize().x/3, m_texture.getSize().y);
}

void PlayerInDoors::out_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position, unsigned int FloorNumber) {
    if (position.x >= map_width)
        setPosition(sf::Vector2f(0.f - m_texture.getSize().x /3, getPosition().y + map_height/FloorNumber));
    else if(position.x < 0.f - m_texture.getSize().x /3)
        setPosition(sf::Vector2f(map_width, getPosition().y - map_height/FloorNumber));
}

void PlayerInDoors::drawInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view){
    inventaire.displayInventory(window, font, view);
}