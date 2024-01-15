// Player.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#define TILESIZE 32

class NPC;
class Obstacle; 

class Player : public sf::Drawable, public sf::Transformable {
public:
    Player() = default;

    Player(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y, unsigned int direction, Inventory inventaire);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Time& deltaTime, TileMap map, sf::View& view, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles, bool is_talking);

    void update_texture(unsigned int u, unsigned int i, sf::Vector2u tileSize,const sf::Time &deltaTime);
    
    bool is_looking_at(NPC npc);

    unsigned int getDirection(){
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

    bool getWallColl(){
        return wall_collision;
    }

    void setWallColl(bool value){
        wall_collision = value;
    }
    
    unsigned int getNbPas(){
        return nb_pas;
    }

    void SetNbPas(unsigned int value){
        nb_pas = value;
    }

    void ResetNbPas(){
        nb_pas = 0;
    }

    void ResetMove(){
        if (going_down  || going_left || going_right || going_up){
            going_down = false;
            going_left = false;
            going_right = false;
            going_up = false;
        }
    }

    Inventory& getInventory(){
        return inventaire;
    }

    void drawInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view);
    // void drawInteractText(sf::RenderWindow& window, sf::Font& font);
protected:
    bool collision_obstacles(sf::Vector2u position, std::vector<Obstacle> obstacles);
    bool collision_npcs(sf::Vector2u position, std::vector<NPC> NPCs);
    bool in_map(unsigned int map_width, unsigned int map_height, sf::Vector2u position);

private:
    // sf::Text InteractText;
    sf::Time elapsed; 
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    sf::Vector2u current_pos;
    unsigned int current_move;
    int change_map;
    unsigned int direction;
    bool can_talk = false;
    bool wall_collision;

    bool going_right = false;
    bool going_left = false;
    bool going_up = false;
    bool going_down = false;
    unsigned int nb_pas;

    Inventory inventaire;

    bool collision(sf::Vector2u position, TileMap map, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles);

};
