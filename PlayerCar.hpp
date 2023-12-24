// PlayerCar.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.hpp"

class PlayerCar : public sf::Drawable, public sf::Transformable {
public:
    PlayerCar(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Time& deltaTime, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<std::vector<int>> plan, std::vector<Obstacle> obstacles);

    void update_texture(unsigned int u, sf::Vector2u tileSize);

    // sf::Vector2u getCurrentPos(){
    //     return current_pos;
    // }

    // void setCurrentPos(sf::Vector2u pos){
    //     current_pos.x =  pos.x;
    //     current_pos.y =  pos.y;
    // }

    // void setChangeMap(int value){
    //     change_map = value;
    // }

    // int getChangeMap(){
    //     return change_map;
    // }

protected:
    bool collision_obstacles(sf::Vector2u position, std::vector<Obstacle> obstacles);
    bool in_map(unsigned int map_width, unsigned int map_height, sf::Vector2u position);

private:
    sf::SoundBuffer buffer;
    sf::SoundBuffer buffer_bump;
    sf::Sound pas_sound;
    sf::Sound bump_sound;
    sf::Time elapsed; 
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    sf::Vector2u current_pos;

    bool collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<Obstacle> obstacles);

};
