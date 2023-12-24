// Player.cpp
#include "Player.hpp"
#include "TileMap.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

PlayerCar::PlayerCar(const std::string &texturePath, unsigned int pos_x, unsigned int pos_y) 
    {

    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
        std::exit(-1);
    }
    if (!buffer.loadFromFile("sound/sound/pas.wav")){
            std::cerr << "Erreur lors du chargement du son" << std::endl;
            std::exit(-1);
        }
    if (!buffer_bump.loadFromFile("sound/sound/bump.wav")){
            std::cerr << "Erreur lors du chargement du son" << std::endl;
            std::exit(-1);
        }
        bump_sound.setBuffer(buffer_bump);
        pas_sound.setBuffer(buffer);
        bump_sound.setVolume(2);
    
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(m_texture.getSize().x / 4, 0.f);
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x / 4, m_texture.getSize().y);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(64.f, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(64.f, 64.f);
    m_vertices[3].texCoords = sf::Vector2f(0.f, 64.f);

    m_vertices[0].color = sf::Color::White;
    m_vertices[1].color = sf::Color::White;
    m_vertices[2].color = sf::Color::White;
    m_vertices[3].color = sf::Color::White;

    setPosition(pos_x * 64.f, pos_y * 64.f);
}

void PlayerCar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

bool PlayerCar::collision_obstacles(sf::Vector2u position, std::vector<Obstacle> obstacles){
    for (Obstacle& obstacle : obstacles){
        if (sf::FloatRect(sf::Vector2f(position.x*ftile_size, position.y*ftile_size), sf::Vector2f(ftile_size, ftile_size)).intersects(obstacle.getGlobalBounds())){
            return true;
        }
    }
    return false;
}

bool PlayerCar::collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<Obstacle> obstacles){
    if (plan[(position.y)][(position.x)] != 0) return true;
    for (Obstacle& obstacle : obstacles){
        if (collision_obstacles(position, obstacles)) return true;
    }
    return false;
}


void PlayerCar::update(const sf::Time& deltaTime, unsigned int map_width, unsigned int map_height, 
                       sf::View& view, std::vector<std::vector<int>> plan, std::vector<Obstacle> obstacles){

}

void PlayerCar::update_texture(unsigned int u, sf::Vector2u tileSize) {
    // m_vertices[0].texCoords = sf::Vector2f(u * tileSize.x, 0.f);
    // m_vertices[1].texCoords = sf::Vector2f((u + 1) * tileSize.x, 0.f);
    // m_vertices[2].texCoords = sf::Vector2f((u + 1) * tileSize.x, tileSize.y);
    // m_vertices[3].texCoords = sf::Vector2f(u * tileSize.x, tileSize.y);
}

bool PlayerCar::in_map(unsigned int map_width, unsigned int map_height, sf::Vector2u position) {
    if (position.x < map_width && position.y < map_height && position.x >= 0 && position.y >= 0)
        return true;
    else
        return false;
}