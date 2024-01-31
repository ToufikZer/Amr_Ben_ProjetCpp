// FraudeGameplay.cpp
#include "FraudeGameplay.hpp"
#include "InGame.hpp"
#include <iostream>

FraudeGameplay::FraudeGameplay(sf::RenderWindow& window, Save save, Inventory inventaire, bool minijeu)
    : window(window),
      map(sf::Vector2u(216, 9)),
      player("texture/texture_char/fraudeur.png", 8, 4, inventaire),
      backmenu(false),
      save(save),
      is_arrived(false),
      minijeu(minijeu)
{
    
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }


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

    if (!map.load("texture/texture_decor/tileset_fraude.png", sf::Vector2u(64, 64), level)) {
        std::cerr << "Erreur lors du chargement de la carte" << std::endl;
        std::exit(-1);
    }
    
    view.setSize(window.getSize().x, map.getHeight() *64);
    view.setCenter(player.getPosition().x + 0.35*view.getSize().x, map.getHeight() *16 + 160);
    view.rotate(90);

    initialize_obstacles();

    initialize_finish();

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
    player.update(deltaTime, font, map.getWidth(), map.getHeight(),view, obstacles);
    if (player.getPosition().x > 210*64.f) 
    {
        player.setSpeed(0);
        is_arrived = true;
        Finish.setPosition(sf::Vector2f(player.getPosition().x + 150.f, player.getPosition().y - 200.f));
    }

}

void FraudeGameplay::draw(sf::RenderWindow& window, sf::Event& event) {
    window.clear();

    window.setView(view);

    window.draw(backgroundSprite);

    window.draw(map);

    for (Obstacle& obstacle : obstacles){
        window.draw(obstacle);
    }

    window.draw(player);

    player.draw_crash(window);
    if (is_arrived) window.draw(Finish);

    window.display();
}

GameState* FraudeGameplay::getNextState() {
    if(backmenu){
        backmenu = false;
        if(!minijeu) return new MainMenu(window, save);
        else return new MiniJeu(window, save);
    }

    if (player.getCrash()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            player.setCrash(false);
            return new FraudeGameplay(window,save, player.getInventory(), minijeu);
        }
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && !minijeu)
        {
            player.setCrash(false);
            return new Indoors(window, save.getName(), save.getPlayerPosition().x, save.getPlayerPosition().y, save.getInventory(), "Frauder ou voler", save.getCombatWin());
        }
    }

    if (is_arrived){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            is_arrived = false;
            if(!minijeu) return new InGame(window, sf::Vector2u(0,1), sf::Vector2f(9,10), sf::Vector2u(16,16), player.getInventory(), 0, "Se rendre au stade", save.getCombatWin());
            else return new MiniJeu(window, save);
        }
    }

    return nullptr;
}

void FraudeGameplay::initialize_obstacles(){
    obstacles.push_back(Obstacle("texture/texture_obstacle/train.png", 16, 6, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train2.png", 36, 3, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 36, 5, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train2.png", 48, 6, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train3.png", 36, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train2.png", 16, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 54, 4, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 54, 5 , 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train2.png", 56, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 63, 5, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 63, 8, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train3.png", 67, 7, 0)); 
    obstacles.push_back(Obstacle("texture/texture_obstacle/train.png", 69, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 77, 5, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 83, 2, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 85, 8, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 87, 4, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 89, 7, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 90, 5, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train3.png", 91, 6, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train.png", 92, 2, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train2.png", 96, 8, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 103, 2, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 103, 6, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train3.png", 107, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 116, 5, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train.png", 116, 3, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train2.png", 136, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 136, 2, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 136, 4, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 140, 3, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 144, 2, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train2.png", 148, 3, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train3.png", 136, 5, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train.png", 116, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 154, 5, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 154, 4, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train2.png", 156, 8, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 163, 2, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 163, 6, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train3.png", 167, 7, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train.png", 169, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 177, 3, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 183, 6, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 185, 7, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 187, 8, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 189, 1, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 190, 2, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train3.png", 191, 4, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train.png", 192, 8, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 203, 3, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/fraude_obstacle.png", 203, 2, 10));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train3.png", 207, 1, 0));
    obstacles.push_back(Obstacle("texture/texture_obstacle/train.png", 209, 8, 0));
}

void FraudeGameplay::initialize_finish(){
    Finish.rotate(90);
    Finish.setFont(font);
    Finish.setStyle(sf::Text::Bold);
    Finish.setString("Bien joue! Entrer pour arriver au stade");
    Finish.setFillColor(sf::Color(30,250,30,250));
    Finish.setCharacterSize(30);
}