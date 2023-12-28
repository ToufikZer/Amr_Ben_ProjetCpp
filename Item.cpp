#include "Item.hpp"

Item::Item(const std::string& name, const std::string& description, int damage, const std::string& texturePath)
    : name(name), description(description), damage(damage) {
    texture.loadFromFile(texturePath);
}

const std::string& Item::getName() const {
    return name;
}

const std::string& Item::getDescription() const {
    return description;
}

int Item::getDamage() const {
    return damage;
}

const sf::Texture& Item::getTexture() const {
    return texture;
}
