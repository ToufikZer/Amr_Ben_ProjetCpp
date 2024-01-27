#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Projectile : public sf::Drawable, public sf::Transformable {
public:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Projectile(float vitesse, unsigned int degats, sf::Vector2f position, const std::string& direction, const std::string& texturePath, int cible);

    void update(const sf::Time& deltaTime, unsigned int map_height);
    float getPositionX() const {
        return position.x;
    }

    float getPositionY() const {
        return position.y;
    }

    int getDegats() const {
        return degats;
    }

    bool getDeleteIt() const {
        return delete_it;
    }
    ~Projectile() {}

private:
    float vitesse;
    unsigned int degats;
    sf::Vector2f position;
    std::string direction;
    bool delete_it;
    int cible
    sf::Sprite sprite;
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
};