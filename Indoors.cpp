// InGame_CarGameplay.cpp
#include "Indoors.hpp"
#include "PlayerIndoors.hpp"
#include <iostream>

Indoors::Indoors(sf::RenderWindow& window)
    : window(window),
      player("texture/texture_char/player.png", 1, 1)
{
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    // if (!music.openFromFile("path/to/music.ogg")) {
    //     std::cerr << "Erreur lors du chargement du son" << std::endl;
    //     std::exit(-1);
    // }

    // music.setVolume(50);
    // music.setLoop(true);
    // music.play();


    // Obstacle obstacle1 = Obstacle("texture/texture_obstacle/giletjaune.png", 5, 2, 0);

    // obstacles.push_back(obstacle1);

    if (!backgroundTexture.loadFromFile("texture/texture_decor/decorgare.jpg")) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    view.reset(sf::FloatRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height));

}

void Indoors::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Gérer les événements ici
}

void Indoors::update(sf::Time deltaTime, sf::RenderWindow& window) {
    player.update(deltaTime, font, window.getSize().x, window.getSize().y ,view, obstacles);
}

void Indoors::draw(sf::RenderWindow& window) {
    // Effacer la fenêtre
    window.clear();

    window.draw(backgroundSprite);

    // Définir la vue
    window.setView(view);
    // Dessiner le joueur
    window.draw(player);

    for (Obstacle& obstacle : obstacles){
        window.draw(obstacle);
    }

    // Afficher la fenêtre
    window.display();
}

GameState* Indoors::getNextState() {
    return nullptr;
}
