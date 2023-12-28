#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.hpp"

class Inventory {
public:
    Inventory();
    Inventory& operator=(const Inventory& other) {
    if (this != &other) {
        items = other.items;
    }
    return *this;
}
    std::vector<Item> getItems(){
        return items;
    }

    void addItem(const Item& item);
    void removeItem(const Item& item_to_remove);
    void exchangeItems(unsigned int index1, unsigned int index2);
    void displayInventory(sf::RenderWindow& window, sf::Font& font, const sf::View& view);

private:
    std::vector<Item> items;
    const unsigned int maxItems;
};
