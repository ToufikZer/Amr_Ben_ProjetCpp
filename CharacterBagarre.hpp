// // CharacterBagarre.hpp
// #pragma once
// #include <SFML/Graphics.hpp>
// #include "PlayerBagarre.hpp"

// class CharacterBagarre : public sf::Drawable, public sf::Transformable {
// public:
//     virtual void update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, sf::View& view, std::vector<Obstacle> obstacles) = 0;
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
//     virtual void update_texture(unsigned int u, unsigned int i);
//     virtual void tir(int degats, float vitesse, sf::Vector2f position, std::string direction);
//     virtual ~CharacterBagarre() {}
// };