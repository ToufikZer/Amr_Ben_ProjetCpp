// Player.cpp
#include "PlayerCar.hpp"

#include "TileMap.hpp"
#include "Obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

PlayerInDoors::PlayerInDoors(const std::string &texturePath, unsigned int pos_x, unsigned int pos_y) :
    speed(0.05)
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

    setPosition(pos_x * 64.f, pos_y * 64.f);

    CrashText.rotate(15);
    CrashText.setStyle(sf::Text::Bold);
    CrashText.setString("You just crashed, press Return to play again");
    CrashText.setFillColor(sf::Color(250,30,30,250));
    CrashText.setCharacterSize(30);
}

void PlayerInDoors::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

bool PlayerInDoors::collision_obstacles(sf::Vector2f position, std::vector<Obstacle> obstacles){
    for (Obstacle& obstacle : obstacles){
        if (sf::FloatRect(sf::Vector2f(position.x + m_texture.getSize().x/9, position.y + m_texture.getSize().y / 9), 
            sf::Vector2f(m_texture.getSize().x*2/9, m_texture.getSize().y*2/9)).intersects(obstacle.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}


void PlayerInDoors::update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<Obstacle> obstacles){
    if(!collision_obstacles(getPosition(),obstacles )){
        move(speed,0.f);
        speed += 0.05;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (in_map(map_width, map_height, sf::Vector2f(getPosition().x, getPosition().y + 2))){
                move(0,2);
                update_texture(2);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            if (in_map(map_width, map_height, sf::Vector2f(getPosition().x, getPosition().y - 2))){
                move(0,-2);
                update_texture(1);
            }
        }
        else{
            update_texture(0);
        }
    }
    view.setCenter(getPosition().x +100, map_height *16 + 160);
}

void PlayerInDoors::update_texture(unsigned int u) {
    m_vertices[0].texCoords = sf::Vector2f(u * m_texture.getSize().x/3, 0.f);
    m_vertices[1].texCoords = sf::Vector2f((u+1) * m_texture.getSize().x/3, 0.f);
    m_vertices[2].texCoords = sf::Vector2f((u+1) * m_texture.getSize().x/3, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(u * m_texture.getSize().x/3, m_texture.getSize().y);
}

bool PlayerInDoors::in_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position) {
    if (position.x < map_width * 64 && position.y < (map_height- 1.5) * 64 && position.x >= 0 && position.y >= 96)
        return true;
    else
        return false;
}