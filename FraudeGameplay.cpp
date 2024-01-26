// FraudeGameplay.cpp
#include "FraudeGameplay.hpp"
#include "InGame.hpp"
#include <iostream>

FraudeGameplay::FraudeGameplay(sf::RenderWindow& window, Save save, Inventory inventaire)
    : window(window),
      map(sf::Vector2u(60, 9)),
      player("texture/texture_char/fraudeur.png", 8, 4, inventaire),
      backmenu(false),
      save(save),
      is_arrived(false)
{
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    view.setSize(window.getSize().x, map.getHeight() *64);
    view.setCenter(player.getPosition().x + 0.35*view.getSize().x, map.getHeight() *16 + 160);
    // if (!music.openFromFile("path/to/music.ogg")) {
    //     std::cerr << "Erreur lors du chargement du son" << std::endl;
    //     std::exit(-1);
    // }

    // music.setVolume(50);
    // music.setLoop(true);
    // music.play();

    level = {
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}
    };

    if (!map.load("texture/texture_decor/tileset_fraude.png", sf::Vector2u(64, 64), level)) {
        std::cerr << "Erreur lors du chargement de la carte" << std::endl;
        std::exit(-1);
    }

    Obstacle obstacle1 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 24, 3, 10);
    Obstacle obstacle2 = Obstacle("texture/texture_obstacle/train.png", 16, 6, 0);
    Obstacle obstacle3 = Obstacle("texture/texture_obstacle/train.png", 36, 3, 0);
    Obstacle obstacle4 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 36, 5, 10);
    Obstacle obstacle5 = Obstacle("texture/texture_obstacle/train2.png", 48, 6, 0);
    Obstacle obstacle6 = Obstacle("texture/texture_obstacle/train3.png", 36, 7, 0);
    Obstacle obstacle7 = Obstacle("texture/texture_obstacle/train2.png", 16, 2, 0);
    Obstacle obstacle8 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 30, 5, 10);

    obstacles.push_back(obstacle1);
    obstacles.push_back(obstacle2);
    obstacles.push_back(obstacle3);
    obstacles.push_back(obstacle4);
    obstacles.push_back(obstacle5);
    obstacles.push_back(obstacle6);
    obstacles.push_back(obstacle7);
    obstacles.push_back(obstacle8);
    

    view.rotate(90);

    Finish.rotate(90);
    Finish.setFont(font);
    Finish.setStyle(sf::Text::Bold);
    Finish.setString("Congrats! Press Return to go near to the CROUS");
    Finish.setFillColor(sf::Color(30,250,30,250));
    Finish.setCharacterSize(30);

    if (!backgroundTexture.loadFromFile("texture/texture_decor/carsBackground.jpg")) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(-1000,-1000);

}

void FraudeGameplay::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            backmenu = true;
        }
    }
}

void FraudeGameplay::update(sf::Time deltaTime, sf::RenderWindow& window) {
    player.update(deltaTime, font, map.getWidth(), map.getHeight(),view, level, obstacles);
    if (player.getPosition().x > 53*64.f) 
    {
        player.setSpeed(0);
        is_arrived = true;
        Finish.setPosition(sf::Vector2f(player.getPosition().x + 150.f, player.getPosition().y - 200.f));
    }

}

void FraudeGameplay::draw(sf::RenderWindow& window, sf::Event& event) {
    // Effacer la fenêtre
    window.clear();

    window.draw(backgroundSprite);

    // Définir la vue
    window.setView(view);

    // Dessiner la carte
    window.draw(map);

    // Dessiner le joueur

    for (Obstacle& obstacle : obstacles){
        window.draw(obstacle);
    }
    window.draw(player);

    player.draw_crash(window);
    if (is_arrived) window.draw(Finish);

    // Afficher la fenêtre
    window.display();
}

GameState* FraudeGameplay::getNextState() {
    if(backmenu){
        backmenu = false;
        music.stop( );
        return new MainMenu(window, save);
    }
    if (player.getCrash()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.setCrash(false);
            return new FraudeGameplay(window,save, player.getInventory());
        }
    }
    if (is_arrived){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            is_arrived = false;
            // return new Indoors(window, "AIRPORT", 40, 120, Inventory());
            return new InGame(window, sf::Vector2u(0,1), sf::Vector2f(9,10), sf::Vector2u(16,16), player.getInventory(), 0, "Se rendre au stade");
        }
    }
    return nullptr;
}
