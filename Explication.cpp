#include <iostream>
#include "Explication.hpp"


Explication::Explication(sf::RenderWindow& window, std::string name, Save save, std::string backgroundPath):
    window(window),
    expl(true),
    name(name),
    save(save)
    {
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0,0);
    }

void Explication::handleEvent(sf::Event& event, sf::RenderWindow& window){
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::E) {
            expl = false;
        }
    }
}

void Explication::update(sf::Time deltaTime, sf::RenderWindow& window){

}

void Explication::draw(sf::RenderWindow& window, sf::Event& event){
    window.clear();
    window.draw(backgroundSprite);

    window.display();

}

GameState* Explication::getNextState(){
    if(!expl){
        expl = true;
        if(name == "lab") return new Labyrinthe(window, 0, sf::Vector2f(15,10), sf::Vector2u(31,21), save.getInventory(), 3);      
        else if(name == "bagarre") return new Bagarre(window, save, save.getInventory(), "texture/texture_decor/2Qpng.png", 2, 20, 1500, 200);
    }

    return nullptr;
}
