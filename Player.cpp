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

Player::Player(const std::string &texturePath, unsigned int pos_x, unsigned int pos_y, unsigned int direction) : 
    current_pos(pos_x, pos_y),
    change_map(0),
    current_move(0) {
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
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x / 4, m_texture.getSize().y / 4);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y / 4);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x / 4, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x / 4, m_texture.getSize().y / 4);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y / 4);

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
    if (direction == 0 && (current_pos.x + 1) == npc.getCurrentPos().x && current_pos.y == npc.getCurrentPos().y)
        return true;
    if (direction == 2 && (current_pos.x) == npc.getCurrentPos().x && current_pos.y - 1 == npc.getCurrentPos().y)
        return true;
    if (direction == 1 && (current_pos.x - 1) == npc.getCurrentPos().x && current_pos.y == npc.getCurrentPos().y)
        return true;
    if (direction == 3 && (current_pos.x) == npc.getCurrentPos().x && current_pos.y + 1 == npc.getCurrentPos().y)
        return true;
    return false;
}

bool Player::collision_obstacles(sf::Vector2u position, std::vector<Obstacle> obstacles){
    for (Obstacle& obstacle : obstacles){
        if (sf::FloatRect(sf::Vector2f(position.x*ftile_size, position.y*ftile_size), sf::Vector2f(ftile_size, ftile_size)).intersects(obstacle.getGlobalBounds())){
            return true;
        }
    }
    return false;
}

bool Player::collision_npcs(sf::Vector2u position, std::vector<NPC> NPCs){
    for (NPC& npc : NPCs){
        if (position.x == npc.getCurrentPos().x && position.y == npc.getCurrentPos().y){
            return true;
        }
    }
    return false;
}

bool Player::collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles){
    if (plan[(position.y)][(position.x)] != 0) return true;
    for (NPC& npc : NPCs){
        if (collision_npcs(position, NPCs)) return true;
    }
    for (Obstacle& obstacle : obstacles){
        if (collision_obstacles(position, obstacles)) return true;
    }
    return false;
}
void Player::update(const sf::Time &deltaTime, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles, bool is_talking) {
    int moveDelay;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) moveDelay = 25;
    else moveDelay = 50;
    sf::Vector2u new_position;
    if (elapsed.asMilliseconds() >= moveDelay) {
        float speed = ftile_size;
    if(!is_talking){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || going_right) {
            new_position.x = (current_pos.x + 1); 
            new_position.y = current_pos.y;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(3);
            else{
                if (collision(new_position, plan,NPCs, obstacles)) bump_sound.play();
                else {
                    if (!going_right) 
                    {
                        std::cout << "1" << std::endl;
                        move(speed/4, 0.f);
                        going_right = true;
                        pas_sound.play();
                    }
                    else{
                        if(current_move != 3)
                        {
                            std::cout << "2" << std::endl;
                            current_move +=1;
                            move(speed/4, 0.f);
                        }
                        else {
                            std::cout << "3" << std::endl;
                            current_move = 0;
                            going_right = false;
                            current_pos.x += 1;
                        }
                    }
                }
            }
            update_texture(2, sf::Vector2u(tile_size, tile_size), deltaTime);
            direction = 0;
            elapsed = sf::Time::Zero;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || going_up) {
            new_position.x = (current_pos.x); 
            new_position.y = current_pos.y - 1;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(2);
            else{
                if (collision(new_position, plan,NPCs, obstacles)) bump_sound.play();
                else {
                    if (!going_up) 
                    {
                        std::cout << "1" << std::endl;
                        move(0.f, -speed/4);
                        going_up = true;
                        pas_sound.play();
                    }
                    else{
                        if(current_move != 3)
                        {
                            std::cout << "2" << std::endl;
                            current_move +=1;
                            move(0.f, -speed/4);
                        }
                        else {
                            std::cout << "3" << std::endl;
                            current_move = 0;
                            going_up = false;
                            current_pos.y -= 1;
                        }
                    }
                }
            }
            update_texture(3, sf::Vector2u(tile_size, tile_size), deltaTime);
            direction = 2;
            elapsed = sf::Time::Zero;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || going_left) {
            new_position.x = (current_pos.x - 1); 
            new_position.y = current_pos.y;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(1);
            else{
                if (collision(new_position, plan,NPCs, obstacles)) bump_sound.play();
                else {
                    if (!going_left) 
                    {
                        std::cout << "1" << std::endl;
                        move(-speed/4, 0.f);
                        going_left = true;
                        pas_sound.play();
                    }
                    else{
                        if(current_move != 3)
                        {
                            std::cout << "2" << std::endl;
                            current_move +=1;
                            move(-speed/4, 0.f);
                        }
                        else {
                            std::cout << "3" << std::endl;
                            current_move = 0;
                            going_left = false;
                            current_pos.x -= 1;
                        }
                    }
                }
            }
            update_texture(1, sf::Vector2u(tile_size, tile_size), deltaTime);
            direction = 1;
            elapsed = sf::Time::Zero;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || going_down) {
            new_position.x = (current_pos.x); 
            new_position.y = current_pos.y +1;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(4);
            else{
                if (collision(new_position, plan,NPCs, obstacles)) bump_sound.play();
                else {
                    if (!going_down) 
                    {
                        std::cout << "1" << std::endl;
                        move(0.f, speed/4);
                        going_down = true;
                        pas_sound.play();
                    }
                    else{
                        if(current_move != 3)
                        {
                            std::cout << "2" << std::endl;
                            current_move +=1;
                            move(0.f, speed/4);
                        }
                        else {
                            std::cout << "3" << std::endl;
                            current_move = 0;
                            going_down = false;
                            current_pos.y += 1;
                        }
                    }
                }
            }
            update_texture(0, sf::Vector2u(tile_size, tile_size), deltaTime);
            direction = 3;
            elapsed = sf::Time::Zero;
        }
    }
    } 
    else {
        elapsed += deltaTime;
    }
    
}

void Player::update_texture(unsigned int u, sf::Vector2u tileSize,const sf::Time &deltaTime) {
    
    for (size_t i = 0; i < 4; i++)
    {
        double tmp_elapsed ;
        if(i == 0)
            tmp_elapsed = elapsed.asMilliseconds();
        std::cout << i << ";" << elapsed.asMilliseconds() - tmp_elapsed <<std::endl;

        if(elapsed.asMilliseconds() - tmp_elapsed >= i * 12.5 && elapsed.asMilliseconds() - tmp_elapsed < (i+1) * 12.5){
            std::cout << "alooo" <<std::endl;
            m_vertices[0].texCoords = sf::Vector2f(i * tileSize.x, u * tileSize.y);
            m_vertices[1].texCoords = sf::Vector2f((i+1)*tileSize.x, u * tileSize.y);
            m_vertices[2].texCoords = sf::Vector2f((i+1)*tileSize.x, (u+1) * tileSize.y);
            m_vertices[3].texCoords = sf::Vector2f(i * tileSize.x, (u+1) * tileSize.y);
        }
        elapsed += deltaTime;
    }
    

}

bool Player::in_map(unsigned int map_width, unsigned int map_height, sf::Vector2u position) {
    if (position.x < map_width && position.y < map_height && position.x >= 0 && position.y >= 0)
        return true;
    else
        return false;
}
