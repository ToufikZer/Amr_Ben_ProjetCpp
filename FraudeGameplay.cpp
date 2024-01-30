// FraudeGameplay.cpp
#include "FraudeGameplay.hpp"
#include "InGame.hpp"
#include <iostream>

FraudeGameplay::FraudeGameplay(sf::RenderWindow& window, Save save, Inventory inventaire)
    : window(window),
      map(sf::Vector2u(108, 9)),
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
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 , 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 5, 0, 1, 0, 1, 0, 1, 0},
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 , 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}
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
    Obstacle obstacle8 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 54, 1, 10);
    Obstacle obstacle9 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 54, 2, 10);
    Obstacle obstacle10 = Obstacle("texture/texture_obstacle/train2.png", 56, 2, 0);
    Obstacle obstacle11 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 63, 3, 10);
    Obstacle obstacle12 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 63, 5, 10);
    Obstacle obstacle13 = Obstacle("texture/texture_obstacle/train3.png", 67, 7, 0);
    Obstacle obstacle14 = Obstacle("texture/texture_obstacle/train.png", 69, 2, 0);
    Obstacle obstacle15 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 77, 5, 10);
    Obstacle obstacle17 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 83, 2, 10);
    Obstacle obstacle18 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 85, 3, 10);
    Obstacle obstacle19 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 87, 4, 10);
    Obstacle obstacle20 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 89, 7, 10);
    Obstacle obstacle21 = Obstacle("texture/texture_obstacle/fraude_obstacle.png", 90, 5, 10);
    Obstacle obstacle22 = Obstacle("texture/texture_obstacle/train3.png", 91, 6, 0);
    Obstacle obstacle23 = Obstacle("texture/texture_obstacle/train.png", 92, 2, 0);

    obstacles.push_back(obstacle1);
    obstacles.push_back(obstacle2);
    obstacles.push_back(obstacle3);
    obstacles.push_back(obstacle4);
    obstacles.push_back(obstacle5);
    obstacles.push_back(obstacle6);
    obstacles.push_back(obstacle7);
    obstacles.push_back(obstacle8);
    obstacles.push_back(obstacle9);
    obstacles.push_back(obstacle10);
    obstacles.push_back(obstacle11);
    obstacles.push_back(obstacle12);
    obstacles.push_back(obstacle13);
    obstacles.push_back(obstacle14);
    obstacles.push_back(obstacle15);
    obstacles.push_back(obstacle17);
    obstacles.push_back(obstacle18);
    obstacles.push_back(obstacle19);
    obstacles.push_back(obstacle20);
    obstacles.push_back(obstacle21);
    obstacles.push_back(obstacle22);
    obstacles.push_back(obstacle23);



    view.rotate(90);

    Finish.rotate(90);
    Finish.setFont(font);
    Finish.setStyle(sf::Text::Bold);
    Finish.setString("Bien joue! Entrer pour arriver au stade");
    Finish.setFillColor(sf::Color(30,250,30,250));
    Finish.setCharacterSize(30);

    if (!backgroundTexture.loadFromFile("texture/texture_decor/carsBackgroundd.jpg")) {
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
    if (player.getPosition().x > 101*64.f) 
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            player.setCrash(false);
            return new FraudeGameplay(window,save, player.getInventory());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.setCrash(false);
            return new Indoors(window, save.getName(), save.getPlayerPosition().x, save.getPlayerPosition().y, save.getInventory(), "Frauder ou voler", save.getCombatWin());
        }
    }
    if (is_arrived){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            is_arrived = false;
            // return new Indoors(window, "AIRPORT", 40, 120, Inventory());
            return new InGame(window, sf::Vector2u(0,1), sf::Vector2f(9,10), sf::Vector2u(16,16), player.getInventory(), 0, "Se rendre au stade", save.getCombatWin());
        }
    }
    return nullptr;
}
