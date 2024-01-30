// InGame_CarGameplay.cpp
#include "InGame_CarGameplay.hpp"
#include "InGame.hpp"
#include <iostream>

InGame_CarGameplay::InGame_CarGameplay(sf::RenderWindow& window, Save save, Inventory inventaire)
    : window(window),
      map(sf::Vector2u(216, 9)),
      player("texture/texture_char/cars_tileset.png", 8, 4, inventaire),
      backmenu(false),
      save(save),
      is_arrived(false)
{
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    view.setCenter(player.getPosition().x + 0.4*window.getSize().x, map.getHeight() *16 + 160);
    view.setSize(window.getSize().x, map.getHeight() *64);
    // if (!music.openFromFile("path/to/music.ogg")) {
    //     std::cerr << "Erreur lors du chargement du son" << std::endl;
    //     std::exit(-1);
    // }

    // music.setVolume(50);
    // music.setLoop(true);
    // music.play();

    level = {
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 , 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 , 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0},
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 , 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 , 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}
    };

    if (!map.load("texture/texture_decor/tileset_car.png", sf::Vector2u(64, 64), level)) {
        std::cerr << "Erreur lors du chargement de la carte" << std::endl;
        std::exit(-1);
    }

    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 16, 3, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 24, 6, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 32, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 40, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 48, 6, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 36, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 16, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 27, 5, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 40, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 47, 1, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 47, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 59, 3, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 59, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 68, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 73, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 79, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 79, 1, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 90, 1, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 90, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 90, 3, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 103, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 103, 5, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 103, 6, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 103, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 116, 3, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 124, 6, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 132, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 140, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 148, 6, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 136, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 116, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 127, 5, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 140, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 147, 1, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 147, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 159, 3, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 159, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 168, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 173, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 179, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 179, 1, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 186, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 188, 1, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 193, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 193, 6, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 197, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 197, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 203, 8, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 205, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/giletjaune.png", 208, 5, 0));
    

    view.rotate(15);

    Finish.rotate(15);
    Finish.setFont(font);
    Finish.setStyle(sf::Text::Bold);
    Finish.setString("Congrats! Press Return to go near to the CROUS");
    Finish.setFillColor(sf::Color(30,250,30,250));
    Finish.setCharacterSize(30);

    if (!backgroundTexture.loadFromFile("texture/texture_decor/carsBackgroundd.jpg")) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(-1000,-1000);

}

void InGame_CarGameplay::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            backmenu = true;
        }
    }
}

void InGame_CarGameplay::update(sf::Time deltaTime, sf::RenderWindow& window) {
    player.update(deltaTime, font, map.getWidth(), map.getHeight(),view, level, obstacles);
    if (player.getPosition().x > 210*64.f) 
    {
        player.setSpeed(0);
        is_arrived = true;
        Finish.setPosition(sf::Vector2f(player.getPosition().x - 200.f, player.getPosition().y - 120.f));
    }

}

void InGame_CarGameplay::draw(sf::RenderWindow& window, sf::Event& event) {
    // Effacer la fenêtre
    window.clear();

    window.draw(backgroundSprite);

    // Définir la vue
    window.setView(view);

    // Dessiner la carte
    window.draw(map);

    // Dessiner le joueur
    window.draw(player);

    for (Obstacle& obstacle : obstacles){
        window.draw(obstacle);
    }

    player.draw_crash(window);
    if (is_arrived) window.draw(Finish);

    // Afficher la fenêtre
    window.display();
}

GameState* InGame_CarGameplay::getNextState() {
    if(backmenu){
        backmenu = false;
        music.stop( );
        return new MainMenu(window, save);
    }
    if (player.getCrash()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.setCrash(false);
            return new InGame_CarGameplay(window,save, player.getInventory());
        }
    }
    if (is_arrived){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            is_arrived = false;
            player.getInventory().setMoney(0);
            // return new Indoors(window, "AIRPORT", 40, 120, Inventory());
            return new InGame(window, sf::Vector2u(0,1), sf::Vector2f(2,3), sf::Vector2u(16,16), player.getInventory(), 0, "Se rendre au CROUS", save.getCombatWin());
        }
    }
    return nullptr;
}
