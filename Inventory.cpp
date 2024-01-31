#include "Inventory.hpp"
#include <iostream>

Inventory::Inventory() : maxItems(3), money(300) {
    
}

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

void Inventory::exchangeItems(const Item& item_to_remove, const Item& item_to_add) {
    if (items.size() == maxItems) {
        removeItem(item_to_remove);
        addItem(item_to_add);
        std::cout << "Objets échangés avec succès." << std::endl;
    } else {
        addItem(item_to_add);
    }
}

void Inventory::displayInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view) {
    // Position des cases
    float xPos = view.getCenter().x - view.getSize().x / 2 + 10.0f;
    float yPos = view.getCenter().y - view.getSize().y / 2 + 10.0f;

    // Taille des cases
    float caseSize = 50.0f;
    money_text.setString(std::to_string(money) + "euros");
    money_text.setPosition(sf::Vector2f(12,65));
    money_text.setFont(font);
    money_text.setCharacterSize(20);
    sf::RectangleShape rectEuro(sf::Vector2f(90,25));
    rectEuro.setPosition(9,65);
    rectEuro.setFillColor(sf::Color(15,45,128,180));
    rectEuro.setOutlineColor(sf::Color(158,45,12));
    rectEuro.setOutlineThickness(2);
    window.draw(rectEuro);
    window.draw(money_text);
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
