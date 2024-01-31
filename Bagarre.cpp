// Bagarre.cpp
#include "Bagarre.hpp"
#include "InGame.hpp"
#include <iostream>

Bagarre::Bagarre(sf::RenderWindow& window, Save save, Inventory inventaire, std::string backgroundPath, std::string ennemiTexturePath, float ennemi_attack_speed, unsigned int ennemi_degats, int attack_delay, int HP, int id_bagarre, bool minijeu)
    : window(window),
      player("texture/texture_char/new_player2.png", 260, 200, inventaire),
      ennemi(ennemiTexturePath, 260, 0, ennemi_attack_speed, ennemi_degats, attack_delay, HP),
      save(save),
      backmenu(false),
      combat_lose(false),
      combat_win(false),
      id_bagarre(id_bagarre),
      minijeu(minijeu),
      skip(false)
{
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0,0);

    view.reset(sf::FloatRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height));

    initialize_finish();

    initialize_lose();

    playerHealthBar.setFillColor(sf::Color::Green);
    playerHealthBar.setPosition(backgroundSprite.getGlobalBounds().width - 110, backgroundSprite.getGlobalBounds().height - 10); 

    ennemiHealthBar.setFillColor(sf::Color::Red);
    ennemiHealthBar.setPosition(10 , 10); 
}

void Bagarre::initialize_finish(){
    
    Finish.setFont(font);
    Finish.setStyle(sf::Text::Bold);
    if (id_bagarre == 0) Finish.setString("Let's go, maintenant tu peux\ndormir chez lui tranquille!\n\nAppuie sur entrer \npour continuer");
    else Finish.setString("FELICITATION!\n\nTU AS TERRASSE ANNIE\nEntrer pour continuer");
    Finish.setFillColor(sf::Color(250,10,10,250));
    Finish.setCharacterSize(30);
    Finish.setPosition(sf::Vector2f(backgroundSprite.getGlobalBounds().width / 5, backgroundSprite.getGlobalBounds().height/4));

    rectFinish.setSize(sf::Vector2f(Finish.getGlobalBounds().width + 20, Finish.getGlobalBounds().height + 20));
    rectFinish.setPosition(Finish.getPosition().x - 10, Finish.getPosition().y - 10);
    rectFinish.setFillColor(sf::Color(0, 56, 168, 250));
    rectFinish.setOutlineColor(sf::Color::White);
    rectFinish.setOutlineThickness(2);
}

void Bagarre::initialize_lose(){
    Lose.setFont(font);
    Lose.setStyle(sf::Text::Bold);
    if (id_bagarre == 0) Lose.setString("HAHAHA t'as perdu la bagarre\nDebrouille toi maintenant!\n\nAppuie sur entrer pour repartir\n ou sur R pour recommencer");
    else if (id_bagarre == 2) Lose.setString("Faut parler au fou de la gare\nPour pas qu'il te tape\n\nAppuie sur entrer pour repartir");
    else Lose.setString("Annie t'as encore humilie\n prend ta revanche avec R");
    Lose.setFillColor(sf::Color(250,10,10,250));
    Lose.setCharacterSize(30);
    Lose.setPosition(sf::Vector2f(backgroundSprite.getGlobalBounds().width / 5, backgroundSprite.getGlobalBounds().height/4));

    rectLose.setSize(sf::Vector2f(Lose.getGlobalBounds().width + 20, Finish.getGlobalBounds().height + 20));
    rectLose.setPosition(Lose.getPosition().x - 10, Finish.getPosition().y - 10);
    rectLose.setFillColor(sf::Color(0, 56, 168, 250));
    rectLose.setOutlineColor(sf::Color::White);
    rectLose.setOutlineThickness(2);
}

void Bagarre::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            backmenu = true;
        }
        if (event.key.code == sf::Keyboard::K) {
            skip = true;
        }
        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::E) {
            if (elapsed.asMilliseconds() > 660) {
                if (player.has_knife()) projs_player.push_back(player.tir(40, 2, sf::Vector2f(player.getPosition().x + 15, player.getPosition().y - 10), "haut"));
                else projs_player.push_back(player.tir(20, 2, sf::Vector2f(player.getPosition().x + 15, player.getPosition().y - 10), "haut"));
                elapsed = sf::Time::Zero;
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left){
            if (elapsed.asMilliseconds() > 660) {
                if (player.has_knife()) projs_player.push_back(player.tir(40, 2, sf::Vector2f(player.getPosition().x + 15, player.getPosition().y - 10), "haut"));
                else projs_player.push_back(player.tir(20, 2, sf::Vector2f(player.getPosition().x + 15, player.getPosition().y - 10), "haut"));
                elapsed = sf::Time::Zero;
            }
        }
    }
}

void Bagarre::update(sf::Time deltaTime, sf::RenderWindow& window) {
    if (player.getHP() <= 0) combat_lose = true;
    if (ennemi.getHP() <= 0) combat_win = true;

    playerHealthBar.setSize(sf::Vector2f(player.getHP() , 10));
    ennemiHealthBar.setSize(sf::Vector2f(ennemi.getHP() / 2, 10));

    if(!combat_win && !combat_lose){
        player.update(deltaTime, font, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height, view);
        ennemi.update(deltaTime, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height, player);
        
        for(Projectile& proj:projs_player){
            proj.update(deltaTime, backgroundSprite.getGlobalBounds().height);
            if (ennemi.collision(proj)) proj.setDeleteIt(true);
            if (proj.getDeleteIt()) projs_player.erase(projs_player.begin());
        }
        elapsed += deltaTime;
    }
}

void Bagarre::draw(sf::RenderWindow& window, sf::Event& event) {
    window.clear();

    window.setView(view);

    window.draw(backgroundSprite);


    window.draw(playerHealthBar);
    window.draw(ennemiHealthBar);

    window.draw(player);
    window.draw(ennemi);

    for (Projectile& proj : projs_player){
        window.draw(proj);
    }
    for (const Projectile& proj : ennemi.getProjsEnnemi()){
        window.draw(proj);
    }

    if (combat_win) {
        window.draw(rectFinish);
        window.draw(Finish);
    }
    if (combat_lose) {
        window.draw(rectLose);
        window.draw(Lose);
    }

    window.display();
}

GameState* Bagarre::getNextState() {
    if(backmenu){
        backmenu = false;
        if(!minijeu) return new MainMenu(window, save);
        else return new MiniJeu(window, save);
    }
    if(skip){
        skip = false;
        if(!minijeu){
                if(id_bagarre != 1) return new Indoors(window, save.getName(), save.getPlayerPosition().x, save.getPlayerPosition().y, save.getInventory(), "Se rendre a la gare", true);
                else return new MiniJeu(window, Save());
            }
            else return new MiniJeu(window, save);
    }
    if(combat_lose){
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && !minijeu)
        {
            combat_lose = false;
            return new Indoors(window, save.getName(), save.getPlayerPosition().x, save.getPlayerPosition().y, save.getInventory(), "Prend ta revanche !", false);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            combat_lose = false;
            return new Bagarre(window, save, player.getInventory(), "texture/texture_decor/2Qpng.png","texture/texture_char/new_player2.png", ennemi.getAttackSpeed(), ennemi.getDegats(), ennemi.getAttackDelay(), ennemi.getHP(), id_bagarre, minijeu);
        }
    }
    
    if (combat_win){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            combat_win = false;
            if(!minijeu){
                if(id_bagarre != 1) return new Indoors(window, save.getName(), save.getPlayerPosition().x, save.getPlayerPosition().y, save.getInventory(), "Se rendre a la gare", true);
                else return new MiniJeu(window, Save());
            }
            else return new MiniJeu(window, save);
        }
    }
    return nullptr;
}
