// Player.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.hpp"
#define TILESIZE 32

class NPC;
class Obstacle; 

class Player : public sf::Drawable, public sf::Transformable {
public:
    Player(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Time& deltaTime, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles, bool is_talking);

    void update_texture(unsigned int u, sf::Vector2u tileSize);

    bool in_map(unsigned int map_width, unsigned int map_height, sf::Vector2u position);

    bool is_looking_at(NPC npc);

    bool collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles);

    std::string getDirection(){
        return direction;
    }

    sf::Vector2u getCurrentPos(){
        return current_pos;
    }

    void setCurrentPos(sf::Vector2u pos){
        current_pos.x =  pos.x;
        current_pos.y =  pos.y;
    }
    void setChangeMap(int value){
        change_map = value;
    }

    int getChangeMap(){
        return change_map;
    }

    sf::FloatRect getGlobalBounds() const {
        return getTransform().transformRect(m_vertices.getBounds());
    }
private:
    sf::SoundBuffer buffer;
    sf::SoundBuffer buffer_bump;
    sf::Sound pas_sound;
    sf::Sound bump_sound;
    sf::Time elapsed;  // Temps écoulé depuis la dernière mise à jour
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    sf::Vector2u current_pos;
    std::string direction;
    bool can_talk = false;
    int change_map;
};
