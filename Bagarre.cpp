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
      combat_lose(false),
      combat_win(false)
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

    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0,0);

    view.reset(sf::FloatRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height));

    Finish.setFont(font);
    Finish.setStyle(sf::Text::Bold);
    Finish.setString("Let's go, maintenant tu peux\ndormir chez lui tranquille!\n\nAppuie sur entrer \npour continuer");
    Finish.setFillColor(sf::Color(250,10,10,250));
    Finish.setCharacterSize(30);
    Finish.setPosition(sf::Vector2f(backgroundSprite.getGlobalBounds().width / 5, backgroundSprite.getGlobalBounds().height/4));

    Lose.setFont(font);
    Lose.setStyle(sf::Text::Bold);
    Lose.setString("HAHAHA t'as perdu la bagarre\nDebrouille toi maintenant!\n\nAppuie sur entrer pour repartir\n ou sur R pour recommencer");
    Lose.setFillColor(sf::Color(250,10,10,250));
    Lose.setCharacterSize(30);
    Lose.setPosition(sf::Vector2f(backgroundSprite.getGlobalBounds().width / 5, backgroundSprite.getGlobalBounds().height/4));

    playerHealthBar.setFillColor(sf::Color::Green);   // Couleur verte
    playerHealthBar.setPosition(backgroundSprite.getGlobalBounds().width - 110, backgroundSprite.getGlobalBounds().height - 10);  // Position de la barre de vie du joueur

    ennemiHealthBar.setFillColor(sf::Color::Red);   // Couleur verte
    ennemiHealthBar.setPosition(10 , 10);  // Position de la barre de vie de l'ennemi
}

void Bagarre::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            backmenu = true;
        }
        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::E) {
            if (elapsed.asMilliseconds() > 330) {
                if (player.has_knife()) projs_player.push_back(player.tir(40, 2, player.getPosition(), "haut"));
                else projs_player.push_back(player.tir(20, 2, player.getPosition(), "haut"));
                elapsed = sf::Time::Zero;
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left){
            if (elapsed.asMilliseconds() > 330) {
                if (player.has_knife()) projs_player.push_back(player.tir(40, 2, player.getPosition(), "haut"));
                else projs_player.push_back(player.tir(20, 2, player.getPosition(), "haut"));
                elapsed = sf::Time::Zero;
            }
        }
    }
}

void Bagarre::update(sf::Time deltaTime, sf::RenderWindow& window) {
    if (player.getHP() <= 0) combat_lose = true;
    // std::cout << projs_player.size() << std::endl;
    if (ennemi.getHP() <= 0) 
    {
        combat_win = true;
    }

    playerHealthBar.setSize(sf::Vector2f(player.getHP() , 10));
    ennemiHealthBar.setSize(sf::Vector2f(ennemi.getHP() / 2, 10));
    if(!combat_win && !combat_lose){
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
    }

}

void Bagarre::draw(sf::RenderWindow& window, sf::Event& event) {
    window.clear();

    window.draw(backgroundSprite);

    // Définir la vue
    window.setView(view);

    window.draw(playerHealthBar);
    window.draw(ennemiHealthBar);


    // Dessiner le joueur
    window.draw(player);
    window.draw(ennemi);

    for (Projectile& proj : projs_player){
        window.draw(proj);
    }
    for (const Projectile& proj : ennemi.getProjsEnnemi()){
        window.draw(proj);
    }

    if (combat_win) window.draw(Finish);
    if (combat_lose) window.draw(Lose);

    // Afficher la fenêtre
    window.display();
}

GameState* Bagarre::getNextState() {
    if(backmenu){
        backmenu = false;
        music.stop( );
        return new MainMenu(window, save);
    }
    if(combat_lose){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            combat_lose = false;
            // return new Indoors(window, "AIRPORT", 40, 120, Inventory());
            return new Indoors(window, save.getName(), save.getPlayerPosition().x, save.getPlayerPosition().y, save.getInventory(), "Prend ta revanche !", false);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            combat_lose = false;
            // return new Indoors(window, "AIRPORT", 40, 120, Inventory());
            return new Bagarre(window, save, player.getInventory(), "texture/texture_decor/2Qpng.png", 2, 20, 1500, 100);
        }
    }
    
    if (combat_win){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            combat_win = false;
            // return new Indoors(window, "AIRPORT", 40, 120, Inventory());
            return new Indoors(window, save.getName(), save.getPlayerPosition().x, save.getPlayerPosition().y, save.getInventory(), "Se rendre a la gare", true);
        }
    }
    return nullptr;
}
