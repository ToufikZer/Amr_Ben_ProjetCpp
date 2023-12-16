// Player.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

class NPC;

class Player : public sf::Drawable, public sf::Transformable {
public:
    Player(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(const sf::Time& deltaTime, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, bool is_talking);

    void update_texture(unsigned int u, sf::Vector2u tileSize);

    bool in_map(unsigned int map_width, unsigned int map_height, sf::Vector2u position);

    bool is_looking_at(NPC npc);

    bool collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs);

    std::string getDirection(){
        return direction;
    }

private:
    sf::Time elapsed;  // Temps écoulé depuis la dernière mise à jour
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    sf::Vector2u current_pos;
    std::string direction;
    bool can_talk = false;
};
