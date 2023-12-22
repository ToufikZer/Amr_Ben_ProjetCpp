// Player.cpp
#include "Player.hpp"
#include "TileMap.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

unsigned int tile_size = TILESIZE;
float ftile_size = static_cast<float> (TILESIZE);

Player::Player(const std::string &texturePath, unsigned int pos_x, unsigned int pos_y) : 
    current_pos(pos_x, pos_y),
    change_map(0) {
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
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x / 4, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x / 4, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].color = sf::Color::White;
    m_vertices[1].color = sf::Color::White;
    m_vertices[2].color = sf::Color::White;
    m_vertices[3].color = sf::Color::White;

    setPosition(pos_x * tile_size, pos_y * tile_size);
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

bool Player::collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles){
    for (NPC& npc : NPCs){
        for (Obstacle& obstacle : obstacles){
            if ((plan[(position.y)][(position.x)] != 0 )
                || 
                (position.x == npc.getCurrentPos().x && position.y == npc.getCurrentPos().y)
                ||
                (sf::FloatRect(sf::Vector2f(position.x*ftile_size, position.y*ftile_size), sf::Vector2f(ftile_size, ftile_size)).intersects(obstacle.getGlobalBounds()))){
                return true;
            }
        }
    }
    return false;
}
void Player::update(const sf::Time &deltaTime, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles, bool is_talking) {
    int moveDelay;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) moveDelay = 250;
    else moveDelay = 500;
    sf::Vector2u new_position;
    if (elapsed.asMilliseconds() >= moveDelay) {
        float speed = ftile_size;
    if(!is_talking){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            // std::cout << "ok" << std::endl;
            new_position.x = (current_pos.x + 1); 
            new_position.y = current_pos.y;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(3);
            else{
                if (collision(new_position, plan,NPCs, obstacles)) bump_sound.play();
                else {
                    move(speed, 0.f);
                    current_pos.x += 1;
                    view.setCenter(getPosition().x + 16.f,getPosition().y+ 16.f);
                    pas_sound.play();
                }
            }
            update_texture(0, sf::Vector2u(tile_size, tile_size));
            direction = "R";
            elapsed = sf::Time::Zero;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            new_position.x = (current_pos.x); 
            new_position.y = current_pos.y - 1;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(2);
            else{
                if (collision(new_position, plan,NPCs, obstacles)) bump_sound.play();
                else {
                    move(0.f, -speed);
                    current_pos.y -= 1;
                    view.setCenter(getPosition().x+ 16.f,getPosition().y+ 16.f);
                    pas_sound.play();
                }
            }
            update_texture(2, sf::Vector2u(tile_size, tile_size));
            direction = "U";
            elapsed = sf::Time::Zero;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            new_position.x = (current_pos.x - 1); 
            new_position.y = current_pos.y;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(1);
            else{
                if (collision(new_position, plan,NPCs, obstacles)) bump_sound.play();
                else {
                    move(-speed, 0.f);
                    current_pos.x -= 1;
                    view.setCenter(getPosition().x+ 16.f, getPosition().y+ 16.f);
                    pas_sound.play();
                }
            }
            update_texture(1, sf::Vector2u(tile_size, tile_size));
            direction = "L";
            elapsed = sf::Time::Zero;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            new_position.x = (current_pos.x); 
            new_position.y = current_pos.y +1;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(4);
            else{
                if (collision(new_position, plan,NPCs, obstacles)) bump_sound.play();
                else {
                    move(0.f, speed);
                    current_pos.y += 1;
                    view.setCenter(getPosition().x + 16.f,getPosition().y+ 16.f);
                    pas_sound.play();
                }
            }
            update_texture(3, sf::Vector2u(tile_size, tile_size));
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

bool Player::in_map(unsigned int map_width, unsigned int map_height, sf::Vector2u position) {
    if (position.x < map_width && position.y < map_height && position.x >= 0 && position.y >= 0)
        return true;
    else
        return false;
}
