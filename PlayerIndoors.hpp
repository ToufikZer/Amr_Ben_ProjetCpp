// PlayerInDoors.hpp
#pragma once

#include "TileMap.hpp"
#include "Obstacle.hpp"
#include "NPC.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
class PlayerInDoors : public sf::Drawable, public sf::Transformable {
public:
    PlayerInDoors(const std::string& texturePath, float pos_x, float pos_y);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<Obstacle> obstacles, std::vector<NPC> NPCs, unsigned int FloorNumber);

    void update_texture(unsigned int u);

    void setSpeed(float value){
        speed = value;
    }

protected:
    bool collision_obstacles(sf::Vector2f position, std::vector<Obstacle> obstacles);
    bool collision_NPCs(sf::Vector2f position, std::vector<NPC> NPCs);
    void out_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position, unsigned int FloorNumber);

private:
    sf::SoundBuffer buffer;
    sf::SoundBuffer buffer_bump;
    sf::Sound pas_sound;
    sf::Sound bump_sound;
    sf::Time elapsed; 
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    float speed;
};
