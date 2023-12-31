// Player.cpp
#include "Player.hpp"
#include "TileMap.hpp"
#include "NPC.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player(const std::string &texturePath, unsigned int pos_x, unsigned int pos_y) : current_pos(pos_x, pos_y) {
    if (!m_texture.loadFromFile(texturePath)) {
        // Gestion de l'erreur si le chargement échoue
        // ...
    }

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(m_texture.getSize().x / 4, 0.f);
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x / 4, m_texture.getSize().y);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x / 4, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x / 4, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].color = sf::Color::White;
    m_vertices[1].color = sf::Color::White;
    m_vertices[2].color = sf::Color::White;
    m_vertices[3].color = sf::Color::White;

    setPosition(pos_x * 32.f, pos_y * 32.f);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

bool Player::is_looking_at(NPC npc) {
    if (direction == "R" && (current_pos.x + 1) == npc.getCurrentPos().x && current_pos.y == npc.getCurrentPos().y)
        return true;
    if (direction == "U" && (current_pos.x) == npc.getCurrentPos().x && current_pos.y - 1 == npc.getCurrentPos().y)
        return true;
    if (direction == "L" && (current_pos.x - 1) == npc.getCurrentPos().x && current_pos.y == npc.getCurrentPos().y)
        return true;
    if (direction == "D" && (current_pos.x) == npc.getCurrentPos().x && current_pos.y + 1 == npc.getCurrentPos().y)
        return true;
    return false;
}

bool Player::collision(const TileMap &map,sf::Vector2u position, const int *plan, std::vector<NPC> NPCs){
    for (NPC& npc : NPCs){
    if ((plan[(position.x) + (position.y) * map.getWidth()] != 0 )
        || 
       (position.x == npc.getCurrentPos().x && position.y == npc.getCurrentPos().y )){
    return true;
    }
    }
    return false;
}
void Player::update(const sf::Time &deltaTime, const TileMap &map, sf::View& view, const int *plan, std::vector<NPC> NPCs, bool is_talking) {
    int moveDelay = 250;
    //can_talk = false;
    sf::Vector2u new_position;
    if (elapsed.asMilliseconds() >= moveDelay) {
        float speed = 32.0f;
    if(!is_talking){
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            new_position.x = (current_pos.x + 1); 
            new_position.y = current_pos.y;
            if (in_map(map, current_pos.x + 1, current_pos.y) && !collision(map,new_position, plan,NPCs)) {
                move(speed, 0.f);
                current_pos.x += 1;
                view.setCenter(getPosition().x + 16.f,getPosition().y+ 16.f);
            }
            update_texture(0, sf::Vector2u(32, 32));
            direction = "R";
            elapsed = sf::Time::Zero;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            new_position.x = (current_pos.x); 
            new_position.y = current_pos.y - 1;
            if (in_map(map, current_pos.x, current_pos.y - 1) && !collision(map,new_position, plan,NPCs)) {
                move(0.f, -speed);
                current_pos.y -= 1;
                view.setCenter(getPosition().x+ 16.f,getPosition().y+ 16.f);
            }
            update_texture(2, sf::Vector2u(32, 32));
            direction = "U";
            elapsed = sf::Time::Zero;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            new_position.x = (current_pos.x - 1); 
            new_position.y = current_pos.y;
            if (in_map(map, current_pos.x - 1, current_pos.y) && !collision(map,new_position, plan,NPCs)) {
                move(-speed, 0.f);
                current_pos.x -= 1;
                view.setCenter(getPosition().x+ 16.f, getPosition().y+ 16.f);
            }
            update_texture(1, sf::Vector2u(32, 32));
            direction = "L";
            elapsed = sf::Time::Zero;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            new_position.x = (current_pos.x); 
            new_position.y = current_pos.y +1;
            if (in_map(map, current_pos.x, current_pos.y + 1) && !collision(map,new_position, plan,NPCs)) {
                move(0.f, speed);
                current_pos.y += 1;
                view.setCenter(getPosition().x + 16.f,getPosition().y+ 16.f);
            }
            update_texture(3, sf::Vector2u(32, 32));
            direction = "D";
            elapsed = sf::Time::Zero;
        }
    }
    } 
    else {
        elapsed += deltaTime;
    }
    
}

void Player::update_texture(unsigned int u, sf::Vector2u tileSize) {
    m_vertices[0].texCoords = sf::Vector2f(u * tileSize.x, 0.f);
    m_vertices[1].texCoords = sf::Vector2f((u + 1) * tileSize.x, 0.f);
    m_vertices[2].texCoords = sf::Vector2f((u + 1) * tileSize.x, tileSize.y);
    m_vertices[3].texCoords = sf::Vector2f(u * tileSize.x, tileSize.y);
}

bool Player::in_map(const TileMap &map, unsigned int i, unsigned int j) {
    if (i < map.getWidth() && j < map.getHeight() && i >= 0 && j >= 0)
        return true;
    else
        return false;
}
