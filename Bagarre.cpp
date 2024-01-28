// Bagarre.cpp
#include "Bagarre.hpp"
#include "InGame.hpp"
#include <iostream>

Bagarre::Bagarre(sf::RenderWindow& window, Save save, Inventory inventaire, std::string backgroundPath, float ennemi_attack_speed, unsigned int ennemi_degats, int attack_delay, int HP)
    : window(window),
      player("texture/texture_char/new_player2.png", 260, 200, inventaire),
      ennemi("texture/texture_char/new_player2.png", 260, 0, ennemi_attack_speed, ennemi_degats, attack_delay, HP),
      backmenu(false),
      save(save),
      is_arrived(false)
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

    

/*
    Finish.setFont(font);
    Finish.setStyle(sf::Text::Bold);
    Finish.setString("Congrats! Press Return to go near to the CROUS");
    Finish.setFillColor(sf::Color(30,250,30,250));
    Finish.setCharacterSize(30);

*/

    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0,0);

    view.reset(sf::FloatRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height));

}

void Bagarre::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            backmenu = true;
        }
        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::E) {
            if (elapsed.asMilliseconds() > 330) {
                projs_player.push_back(player.tir(20, 2, player.getPosition(), "haut"));
                elapsed = sf::Time::Zero;
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left){
            if (elapsed.asMilliseconds() > 330) {
                projs_player.push_back(player.tir(20, 2, player.getPosition(), "haut"));
                elapsed = sf::Time::Zero;
            }
        }
    }
}

void Bagarre::update(sf::Time deltaTime, sf::RenderWindow& window) {
    player.update(deltaTime, font, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height ,view, obstacles);
    ennemi.update(deltaTime, font, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height ,view, obstacles, player);
    for(Projectile& proj:projs_player){
        proj.update(deltaTime, backgroundSprite.getGlobalBounds().height);
        if (ennemi.collision(proj)) proj.setDeleteIt(true);
        if (proj.getDeleteIt()) {
            projs_player.erase(projs_player.begin());
        }
    }
    elapsed += deltaTime;
    // std::cout << projs_player.size() << std::endl;
    // if (ennemi.getHP <= 0) 
    // {
    //     ILEMOR
    //     player.setSpeed(0);
    //     is_arrived = true;
    //     Finish.setPosition(sf::Vector2f(player.getPosition().x - 200.f, player.getPosition().y - 120.f));
    // }

}

void Bagarre::draw(sf::RenderWindow& window, sf::Event& event) {
    // Effacer la fenêtre
    //std::cout << "aalalala" << std::endl;
    window.clear();
    //std::cout << "olololol" << std::endl;

    window.draw(backgroundSprite);

    // Définir la vue
    window.setView(view);


    // Dessiner le joueur
    window.draw(player);
    window.draw(ennemi);

    for (Projectile& proj : projs_player){
        window.draw(proj);
    }
    for (const Projectile& proj : ennemi.getProjsEnnemi()){
        window.draw(proj);
    }

    if (is_arrived) window.draw(Finish);

    // Afficher la fenêtre
    window.display();
}

GameState* Bagarre::getNextState() {
    if(backmenu){
        backmenu = false;
        music.stop( );
        return new MainMenu(window, save);
    }
    // if (player.getCrash()){
    //     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    //     {
    //         player.setCrash(false);
    //         return new Bagarre(window,save, player.getInventory());
    //     }
    // }
    // if (is_arrived){
    //     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    //     {
    //         is_arrived = false;
    //         // return new Indoors(window, "AIRPORT", 40, 120, Inventory());
    //         return new InGame(window, sf::Vector2u(0,1), sf::Vector2f(2,3), sf::Vector2u(16,16), player.getInventory(), 0, "Se rendre au CROUS");
    //     }
    // }
    return nullptr;
}
