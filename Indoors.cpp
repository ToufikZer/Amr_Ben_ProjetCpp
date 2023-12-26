// InGame_CarGameplay.cpp
#include "Indoors.hpp"
#include "PlayerIndoors.hpp"
#include "MapInstances.hpp"
#include <iostream>

MapIndoors GARE = MAP5;
MapIndoors MARIO = MAP6;

Indoors::Indoors(sf::RenderWindow& window, std::string MapName)
    : window(window),
      player("texture/texture_char/player.png", 64.f, 105.f),
      back_to_town(false),
      next_town(false)
{
    MapList.push_back(GARE);
    MapList.push_back(MARIO);

    for (MapIndoors& map: MapList){
        if (MapName == map.getName()){
            BackgroundPath = map.getBackgroundPath();
            NPCs = map.getNPCs();
            obstacles = map.getObstacles();
            MusicPath = map.getMusicPath();
            FloorNumber = map.getFloorNb();
            break;
        }
    }

    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    // if (!music.openFromFile(MusicPath)) {
    //     std::cerr << "Erreur lors du chargement du son" << std::endl;
    //     std::exit(-1);
    // }

    // music.setVolume(5);
    // music.setLoop(true);
    // music.play();
    if (!backgroundTexture.loadFromFile(BackgroundPath)) {
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
    player.update(deltaTime, font, backgroundSprite.getGlobalBounds().width,
                  backgroundSprite.getGlobalBounds().height, view, obstacles, FloorNumber);
    if (player.getPosition().y <= 0.f){
        back_to_town = true;
    }
    if (player.getPosition().y >= backgroundSprite.getGlobalBounds().height){
        next_town = true;
    }
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

    for (NPC& npc : NPCs){
        window.draw(npc);
    }
    // Afficher la fenêtre
    window.display();
}

GameState* Indoors::getNextState() {
    if (back_to_town){
        back_to_town = false;
        return new InGame(window, sf::Vector2u(0,2), sf::Vector2u(10,7), sf::Vector2u(16,16), 3);
    }
    if (next_town){
        next_town = false;
        return new InGame(window, sf::Vector2u(0,0), sf::Vector2u(3,3), sf::Vector2u(16,16), 0);
    }
    return nullptr;
}
