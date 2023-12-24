// InGame_CarGameplay.cpp
#include "InGame_CarGameplay.hpp"
#include <iostream>

InGame_CarGameplay::InGame_CarGameplay(sf::RenderWindow& window)
    : window(window),
      map(sf::Vector2u(30, 10)),
    //   view(sf::Vector2f(80, 80), sf::Vector2f(160, 160)),
      player("texture/texture_char/char_tileset.png", 0, 0, 0) // Adapter les paramètres en fonction de votre classe Player
{
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    view.setCenter(map.getWidth()* 16 - 200, map.getHeight() *16);
    view.setSize(800, map.getHeight() *64);
    // if (!music.openFromFile("path/to/music.ogg")) {
    //     std::cerr << "Erreur lors du chargement du son" << std::endl;
    //     std::exit(-1);
    // }

    // music.setVolume(50);
    // music.setLoop(true);
    // music.play();

    // Initialiser la carte (à remplacer par votre propre logique)
    // Exemple : charger le niveau depuis un fichier, générer aléatoirement, etc.
    level = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1}
    };

    if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(32, 32), level)) {
        std::cerr << "Erreur lors du chargement de la carte" << std::endl;
        std::exit(-1);
    }
    view.rotate(15);

}

void InGame_CarGameplay::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Gérer les événements ici
}

void InGame_CarGameplay::update(sf::Time deltaTime, sf::RenderWindow& window) {
    
}

void InGame_CarGameplay::draw(sf::RenderWindow& window) {
    // Effacer la fenêtre
    window.clear();

    sf::RectangleShape background(sf::Vector2f(4000, 4000));
    background.setFillColor(sf::Color(0, 0, 255)); // Couleur bleue
    background.setPosition(sf::Vector2f(-1000,-1000));
    window.draw(background);

    // Définir la vue
    window.setView(view);

    // Dessiner la carte
    window.draw(map);

    // Dessiner le joueur
    window.draw(player);

    // Afficher la fenêtre
    window.display();
}

GameState* InGame_CarGameplay::getNextState() {
    // Retourner le prochain état du jeu (à implémenter selon votre logique)
    return nullptr;
}
