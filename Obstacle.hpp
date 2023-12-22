#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"

class Obstacle : public sf::Drawable, public sf::Transformable {
public:
    Obstacle() = default;
    Obstacle(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y, sf::Vector2u ChangeTile1, sf::Vector2u ChangeTile2, std::string direction_to_enter);
    Obstacle(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y, sf::Vector2u ChangeTile1, std::string direction_to_enter);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(Player& player, const sf::Time &deltaTime);

    void update_texture(unsigned int u);

    sf::FloatRect getGlobalBounds() const {
        return getTransform().transformRect(m_vertices.getBounds());
    }

    bool getCanEnter(){
        return can_enter;
    }

    void setCanEnter(bool value){
        can_enter = value;
    }
private:
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    bool is_open;
    bool can_enter;
    sf::Vector2u ChangeTile1;
    sf::Vector2u ChangeTile2;
    std::string direction_to_enter;
};

