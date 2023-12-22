#include "Obstacle.hpp"
#include "Player.hpp"
#include "iostream"

unsigned int tile_size_obstacle = TILESIZE;
float ftile_size_obstacle = static_cast<float> (TILESIZE);

Obstacle::Obstacle(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y){
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
        std::exit(-1);
    }

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(m_texture.getSize().x, 0.f);
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y);

    setPosition(pos_x * ftile_size_obstacle, pos_y * ftile_size_obstacle);
}

void Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}