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
    view.reset(sf::FloatRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height));
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
    window.setView(view);
    window.display();

}

GameState* Explication::getNextState(){
    if(!expl){
        expl = true;
        if(name == "lab") return new Labyrinthe(window, 0, sf::Vector2f(15,10), sf::Vector2u(31,21), save.getInventory(), 3);      
        else if(name == "bagarre") return new Bagarre(window, save, save.getInventory(), "texture/texture_decor/2Qpng.png", 8, 20, 800, 400);
        // POUR ANNIE D'ALGOAT 
        //else if(name == "bagarre_2") return new Bagarre(window, save, save.getInventory(), "texture/texture_decor/2Qpng.png", 8, 40, 500, 800);
        else if(name == "car") return new InGame_CarGameplay(window, Save("InDoors", save.getPlayerPosition(), save.getName(), save.getInventory(), true, save.getCombatWin()), save.getInventory());
        else if(name == "fraude") return new FraudeGameplay(window, Save("InGame", sf::Vector2f(save.getPlayerPosition().x, save.getPlayerPosition().y), sf::Vector2u(save.getCurrentMap().x, save.getCurrentMap().y), sf::Vector2u(save.getCurrentMap().x, save.getCurrentMap().y), save.getInventory(), true, save.getCombatWin()), save.getInventory());
    }

    return nullptr;
}
