#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Item {
public:
    Item(const std::string& name, const std::string& description, int damage, const std::string& texturePath);
    Item& operator=(const Item& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        damage = other.damage;
        texture = other.texture;
    }
    return *this;
}
    const std::string& getName() const;
    const std::string& getDescription() const;
    int getDamage() const;
    const sf::Texture& getTexture() const;

private:
    std::string name;
    std::string description;
    int damage;
    sf::Texture texture;
};
