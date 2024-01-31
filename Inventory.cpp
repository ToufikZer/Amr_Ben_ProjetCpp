#include "Inventory.hpp"
#include <iostream>

Inventory::Inventory() : maxItems(3), money(300) {}

void Inventory::addItem(const Item& item) { //ajout d'un item dans l'inventaire
    if (items.size() < maxItems) {
        items.push_back(item);
    }
}

void Inventory::removeItem(const Item& item_to_remove) { //retrait d'un item de l'inventaire
    if (!items.empty()){
        int index = 0;
        for (Item& item : items){
            if (item.getName() == item_to_remove.getName()) break;
            else index++;
        }
        items.erase(items.begin() + index);
    }
}

void Inventory::displayInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view) { //affichage de l'inventaire
    float xPos = view.getCenter().x - view.getSize().x / 2 + 10.0f;
    float yPos = view.getCenter().y - view.getSize().y / 2 + 10.0f;

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
    
    for (unsigned int i = 0; i < maxItems; ++i) {
        sf::RectangleShape itemBox(sf::Vector2f(caseSize, caseSize));
        itemBox.setPosition(xPos, yPos);
        itemBox.setFillColor(sf::Color(150, 150, 150, 150));
        window.draw(itemBox);

        xPos += caseSize + 10.0f;
    }

    for (size_t i = 0; i < items.size(); ++i) {
        sf::Sprite itemSprite(items[i].getTexture());
        itemSprite.setPosition(view.getCenter().x - view.getSize().x / 2 + 10.0f + i * (caseSize + 10.0f), view.getCenter().y - view.getSize().y / 2 + 10.0f);
        window.draw(itemSprite);
    }
}
