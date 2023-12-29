// Player.cpp
#include "PlayerCar.hpp"

#include "TileMap.hpp"
#include "Obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

PlayerCar::PlayerCar(const std::string &texturePath, unsigned int pos_x, unsigned int pos_y) :
    crash(false),
    speed(0.2)
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

    setPosition(pos_x * 64.f, pos_y * 64.f);

    CrashText.rotate(15);
    CrashText.setStyle(sf::Text::Bold);
    CrashText.setString("You just crashed, press Return to play again");
    CrashText.setFillColor(sf::Color(250,30,30,250));
    CrashText.setCharacterSize(30);
}

void PlayerCar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

bool PlayerCar::collision_obstacles(sf::Vector2f position, std::vector<Obstacle> obstacles){
    for (Obstacle& obstacle : obstacles){
        if (sf::FloatRect(sf::Vector2f(position.x + m_texture.getSize().x/9, position.y + m_texture.getSize().y / 9), 
            sf::Vector2f(m_texture.getSize().x*2/9, m_texture.getSize().y*2/9)).intersects(obstacle.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}


void PlayerCar::update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, 
                       sf::View& view, std::vector<std::vector<int>> plan, std::vector<Obstacle> obstacles){
    if(!collision_obstacles(getPosition(),obstacles ) && !crash){
        float deltaTimeSeconds = deltaTime.asSeconds();
        float speedIncrease = 0.3f;
        move(speed * deltaTimeSeconds,0.f);
        speed += speedIncrease;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (in_map(map_width, map_height, sf::Vector2f(getPosition().x, getPosition().y + speed * deltaTimeSeconds*0.75))){
                move(0,speed * deltaTimeSeconds*0.25);
                update_texture(2);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            if (in_map(map_width, map_height, sf::Vector2f(getPosition().x, getPosition().y - speed * deltaTimeSeconds*0.75))){
                move(0,-speed * deltaTimeSeconds*0.25);
                update_texture(1);
            }
        }
        else{
            update_texture(0);
        }
    }
    else{
        CrashText.setFont(font);
        CrashText.setPosition(sf::Vector2f(getPosition().x - m_texture.getSize().x / 2 - 80, getPosition().y - 120));
        crash = true;
        if (speed > 0)
        {
            move(speed * deltaTime.asSeconds(),0.f);
            speed -= 1;
            rotate(5);
        }
    }
    view.setCenter(getPosition().x +100, map_height *16 + 160);
}

void PlayerCar::draw_crash(sf::RenderWindow& window){
    if (crash) {
        window.draw(CrashText);
    }
}


void PlayerCar::update_texture(unsigned int u) {
    m_vertices[0].texCoords = sf::Vector2f(u * m_texture.getSize().x/3, 0.f);
    m_vertices[1].texCoords = sf::Vector2f((u+1) * m_texture.getSize().x/3, 0.f);
    m_vertices[2].texCoords = sf::Vector2f((u+1) * m_texture.getSize().x/3, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(u * m_texture.getSize().x/3, m_texture.getSize().y);
}

bool PlayerCar::in_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position) {
    if (position.x < map_width * 64 && position.y < (map_height- 1.5) * 64 && position.x >= 0 && position.y >= 96)
        return true;
    else
        return false;
}