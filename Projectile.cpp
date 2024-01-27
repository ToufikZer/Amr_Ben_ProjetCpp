#include "Projectile.hpp"
#include <iostream>

Projectile::Projectile(float vitesse, int degats, sf::Vector2f position, const std::string& direction, const std::string& texturePath)
    : vitesse(vitesse), degats(degats), position(position), direction(direction)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture du projectile depuis : " << texturePath << std::endl;
    }

    sprite.setTexture(texture);
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

void Projectile::update(const sf::Time& deltaTime, unsigned int map_height) {
    if (direction == "haut") {
        move(0, -vitesse * deltaTime.asSeconds());
    } else if (direction == "bas") {
        move(0, vitesse * deltaTime.asSeconds());
    }

}
