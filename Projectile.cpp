#include "Projectile.hpp"
#include <iostream>

Projectile::Projectile(float vitesse, unsigned int degats, sf::Vector2f position, const std::string& direction, const std::string& texturePath, int cible)
    : vitesse(vitesse), degats(degats), position(position), direction(direction), delete_it(false), cible(cible)
{
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

    setPosition(position.x, position.y);
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

void Projectile::update(const sf::Time& deltaTime, unsigned int map_height) {
    if (direction == "haut") {
        move(0, -vitesse);

    } else if (direction == "bas") {
        move(0, vitesse);
        std::cout << vitesse << std::endl;
    }
    if (getPosition().y < 0 || getPosition().y > map_height) {
        delete_it = true;
    }
}

bool Projectile::collision(){
    if(cible == 0){
        //Vise le player

    }
    else{
        //Vise l'ennemi
        
    }
}
