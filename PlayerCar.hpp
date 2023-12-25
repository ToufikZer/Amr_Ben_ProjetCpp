// PlayerCar.hpp
#pragma once

#include "TileMap.hpp"
#include "Obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
class PlayerCar : public sf::Drawable, public sf::Transformable {
public:
    PlayerCar(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<std::vector<int>> plan, std::vector<Obstacle> obstacles);

    void update_texture(unsigned int u);

    void draw_crash(sf::RenderWindow& window);

    void setSpeed(float value){
        speed = value;
    }

    bool getCrash(){
        return crash;
    }

    void setCrash(bool value){
        crash = value;
    }

protected:
    bool collision_obstacles(sf::Vector2f position, std::vector<Obstacle> obstacles);
    bool in_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position);

private:
    sf::SoundBuffer buffer;
    sf::SoundBuffer buffer_bump;
    sf::Sound pas_sound;
    sf::Sound bump_sound;
    sf::Time elapsed; 
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    float speed;

    bool crash;
    sf::Text CrashText;

};
