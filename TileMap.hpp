// TileMap.hpp
#pragma once

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    TileMap(sf::Vector2u dimension);

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    unsigned int width;
    unsigned int height;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};
