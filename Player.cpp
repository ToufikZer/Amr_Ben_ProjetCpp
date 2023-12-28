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

Player::Player(const std::string &texturePath, unsigned int pos_x, unsigned int pos_y, unsigned int direction, Inventory inventaire) : 
    current_pos(pos_x, pos_y),
    change_map(0),
    current_move(0),
    wall_collision(false),
    inventaire(inventaire) {
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
        std::exit(-1);
    }

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
    if (collision_npcs(position, NPCs)) return true;
    if (collision_obstacles(position, obstacles)) return true;
    return false;
}
void Player::update(const sf::Time &deltaTime, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles, bool is_talking) {
    int moveDelay;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) moveDelay = 15;
    else moveDelay = 30;
    sf::Vector2u new_position;
    if (elapsed.asMilliseconds() >= moveDelay) {
        float speed = ftile_size;
    if(!is_talking){
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || going_right) && !going_down && !going_left && !going_up) {
            new_position.x = (current_pos.x + 1); 
            new_position.y = current_pos.y;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(3);
            else{
                if (collision(new_position, plan,NPCs, obstacles)){wall_collision = true;}
                else {
                    if (!going_right) 
                    {
                        move(speed/4, 0.f);
                        going_right = true;
                    }
                    else{
                        if(current_move != 3)
                        {
                            current_move +=1;
                            move(speed/4, 0.f);
                        }
                        else {
                            current_move = 0;
                            going_right = false;
                            current_pos.x += 1;
                        }
                    }
                }
            }
            update_texture(2,current_move, sf::Vector2u(tile_size, tile_size), deltaTime);
            direction = 0;
            elapsed = sf::Time::Zero;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || going_up) && !going_down && !going_left && !going_right) {
            new_position.x = (current_pos.x); 
            new_position.y = current_pos.y - 1;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(2);
            else{
                if (collision(new_position, plan,NPCs, obstacles)){wall_collision = true;}
                else {
                    if (!going_up) 
                    {
                        move(0.f, -speed/4);
                        going_up = true;
                    }
                    else{
                        if(current_move != 3)
                        {
                            current_move +=1;
                            move(0.f, -speed/4);
                        }
                        else {
                            current_move = 0;
                            going_up = false;
                            current_pos.y -= 1;
                        }
                    }
                }
            }
            update_texture(3,current_move, sf::Vector2u(tile_size, tile_size), deltaTime);
            direction = 2;
            elapsed = sf::Time::Zero;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || going_left) && !going_down && !going_right && !going_up) {
            new_position.x = (current_pos.x - 1); 
            new_position.y = current_pos.y;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(1);
            else{
                if (collision(new_position, plan,NPCs, obstacles)){wall_collision = true;}
                else {
                    if (!going_left) 
                    {
                        move(-speed/4, 0.f);
                        going_left = true;
                    }
                    else{
                        if(current_move != 3)
                        {
                            current_move +=1;
                            move(-speed/4, 0.f);
                        }
                        else {
                            current_move = 0;
                            going_left = false;
                            current_pos.x -= 1;
                        }
                    }
                }
            }
            update_texture(1,current_move, sf::Vector2u(tile_size, tile_size), deltaTime);
            direction = 1;
            elapsed = sf::Time::Zero;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || going_down) && !going_right && !going_left && !going_up) {
            new_position.x = (current_pos.x); 
            new_position.y = current_pos.y +1;
            if(!in_map(map_width, map_height, new_position)) setChangeMap(4);
            else{
                if (collision(new_position, plan,NPCs, obstacles)){wall_collision = true;}
                else {
                    if (!going_down) 
                    {
                        move(0.f, speed/4);
                        going_down = true;
                    }
                    else{
                        if(current_move != 3)
                        {
                            current_move +=1;
                            move(0.f, speed/4);
                        }
                        else {
                            current_move = 0;
                            going_down = false;
                            current_pos.y += 1;
                        }
                    }
                }
            }
            update_texture(0,current_move, sf::Vector2u(tile_size, tile_size), deltaTime);
            direction = 3;
            elapsed = sf::Time::Zero;
        }
    }
    } 
    else {
        elapsed += deltaTime;
    }
}

void Player::update_texture(unsigned int u, unsigned int i, sf::Vector2u tileSize,const sf::Time &deltaTime) {
        m_vertices[0].texCoords = sf::Vector2f(i * tileSize.x, u * tileSize.y);
        m_vertices[1].texCoords = sf::Vector2f((i+1)*tileSize.x, u * tileSize.y);
        m_vertices[2].texCoords = sf::Vector2f((i+1)*tileSize.x, (u+1) * tileSize.y);
        m_vertices[3].texCoords = sf::Vector2f(i * tileSize.x, (u+1) * tileSize.y);
}

bool Player::in_map(unsigned int map_width, unsigned int map_height, sf::Vector2u position) {
    if (position.x < map_width && position.y < map_height && position.x >= 0 && position.y >= 0)
        return true;
    else
        return false;
}

void Player::drawInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view){
    inventaire.displayInventory(window, font, view);
}

