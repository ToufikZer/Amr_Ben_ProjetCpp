#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"

class Obstacle : public sf::Drawable, public sf::Transformable {
public:
    Obstacle() = default;
    Obstacle(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update_texture(Player player, unsigned int u,unsigned int v, sf::Vector2f tileSize);

    sf::FloatRect getGlobalBounds() const {
        return getTransform().transformRect(m_vertices.getBounds());
    }
private:
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
};
