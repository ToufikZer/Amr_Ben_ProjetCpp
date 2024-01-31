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
    window.setView(view);
    window.draw(backgroundSprite);
    window.display();

}

GameState* Explication::getNextState(){
    if(!expl){
        expl = true;
        if(name == "lab") return new Labyrinthe(window, 0, sf::Vector2f(15,10), sf::Vector2u(31,21), save.getInventory(), 3);      
        else if(name == "bagarre") return new Bagarre(window, save, save.getInventory(), "texture/texture_decor/2Qpng.png","texture/texture_char/etudiant.png", 8, 20, 800, 400, 0, false);
        else if(name == "bagarre_2") return new Bagarre(window, save, save.getInventory(), "texture/texture_decor/2Qpng.png","texture/texture_char/new_player2.png", 8, 40, 500, 800, 1, false);
        else if(name == "car") return new InGame_CarGameplay(window, save, save.getInventory(), false);
        else if(name == "fraude") return new FraudeGameplay(window, save, save.getInventory(), false);
        else if(name == "start") return new Indoors(window, "AIRPORT", 40, 120, Inventory(), "Trouver un endroit ou dormir", false);
        else if(name == "fin") return new MiniJeu(window, save);
    }

    return nullptr;
}
