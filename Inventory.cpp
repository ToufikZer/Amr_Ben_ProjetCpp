#include "Inventory.hpp"
#include <iostream>

Inventory::Inventory() : maxItems(3) {}

void Inventory::addItem(const Item& item) {
    if (items.size() < maxItems) {
        items.push_back(item);
    } else {
        std::cout << "L'inventaire est plein, impossible d'ajouter plus d'objets." << std::endl;
    }
}

void Inventory::removeItem(const Item& item_to_remove) {
    if (!items.empty()){
        int index = 0;
        for (Item& item : items){
            if (item.getName() == item_to_remove.getName()) break;
            else index++;
        }
        items.erase(items.begin() + index);
    }
}

void Inventory::exchangeItems(unsigned int index1, unsigned int index2) {
    if (index1 < items.size() && index2 < items.size()) {
        std::swap(items[index1], items[index2]);
        std::cout << "Objets échangés avec succès." << std::endl;
    } else {
        std::cout << "Index d'objet invalide pour l'échange." << std::endl;
    }
}

void Inventory::displayInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view) {
    // Position des cases
    float xPos = view.getCenter().x - view.getSize().x / 2 + 10.0f;
    float yPos = view.getCenter().y - view.getSize().y / 2 + 10.0f;

    // Taille des cases
    float caseSize = 50.0f;

    // Dessiner les cases vides
    for (unsigned int i = 0; i < maxItems; ++i) {
        sf::RectangleShape itemBox(sf::Vector2f(caseSize, caseSize));
        itemBox.setPosition(xPos, yPos);
        itemBox.setFillColor(sf::Color(150, 150, 150, 150));
        window.draw(itemBox);

        // Décaler la position pour la prochaine case
        xPos += caseSize + 10.0f;
    }

    // Dessiner les textures des items
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Sprite itemSprite(items[i].getTexture());
        itemSprite.setPosition(view.getCenter().x - view.getSize().x / 2 + 10.0f + i * (caseSize + 10.0f), view.getCenter().y - view.getSize().y / 2 + 10.0f);
        window.draw(itemSprite);
    }
}
