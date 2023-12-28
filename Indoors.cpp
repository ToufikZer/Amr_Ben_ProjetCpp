// InGame_CarGameplay.cpp
#include "Indoors.hpp"
#include "PlayerIndoors.hpp"
#include "MapInstances.hpp"
#include <iostream>

MapIndoors GARE = MAP5;
MapIndoors MARIO = MAP6;
MapIndoors CROUS = MAP7;
MapIndoors KITCHEN = MAP8;

Indoors::Indoors(sf::RenderWindow& window, std::string MapName, float pos_player_x, float pos_player_y, bool has_key)
    : window(window),
      player("texture/texture_char/player.png", pos_player_x, pos_player_y),
      back_to_town(false),
      next_town(false),
      kitchen(false),
      has_key(has_key),
      currentMessage(0)
{
    MapList.push_back(GARE);
    MapList.push_back(MARIO);
    MapList.push_back(CROUS);
    MapList.push_back(KITCHEN);

    for (MapIndoors& map: MapList){
        if (MapName == map.getName()){
            BackgroundPath = map.getBackgroundPath();
            NPCs = map.getNPCs();
            obstacles = map.getObstacles();
            MusicPath = map.getMusicPath();
            FloorNumber = map.getFloorNb();
            PlayerSpeed = map.getPlayerSpeed();
            break;
        }
    }

    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    if (!music.openFromFile(MusicPath)) {
        std::cerr << "Erreur lors du chargement du son" << std::endl;
        std::exit(-1);
    }

    music.setVolume(5);
    music.setLoop(true);
    music.play();
    if (!backgroundTexture.loadFromFile(BackgroundPath)) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    player.setSpeed(PlayerSpeed);
    view.reset(sf::FloatRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height));

}

void Indoors::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            for (NPC& npc : NPCs) {
                if (player.collision_NPCs(sf::Vector2f(player.getPosition().x,player.getPosition().y), npc)) {
                    if (npc.getDialogue()[currentMessage] == "EXIT") {
                        back_to_town = true;
                        music.stop();
                    }
                    else if (npc.getDialogue()[currentMessage] == "CUISINE"){
                        kitchen = true;
                        music.stop();
                    }
                    else if (has_key && npc.getDialogue()[currentMessage] == "Oh, the doors seems to be half-open"){
                        std::cout << "BAGARRE" << std::endl;
                    }
                    
                    else if (npc.getDialogue()[currentMessage] == "ROOM KEY ??"){
                        isTalking = true;
                        has_key = true;
                        npc.setIsTalking(true);
                        npcThatWasTalking = &npc;
                        currentMessage += 1;
                        break;
                    }
                    else{
                        if (!isTalking){
                            music.pause();
                            npc.play_toctoc();
                            music.play();
                            isTalking = true;
                            npc.setIsTalking(true);
                            npcThatWasTalking = &npc;
                            break;
                        }
                        else if ((&npc == npcThatWasTalking) && isTalking && (currentMessage < npc.getDialogue().size() - 1))
                    {
                        currentMessage += 1;
                        break;
                    }
                        else {
                            if (npcThatWasTalking != nullptr) {
                                if (&npc == npcThatWasTalking) {
                                    isTalking = false;
                                    currentMessage = 0;
                                    npcThatWasTalking->setIsTalking(false);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Indoors::update(sf::Time deltaTime, sf::RenderWindow& window) {
    player.update(deltaTime, font, backgroundSprite.getGlobalBounds().width,
                  backgroundSprite.getGlobalBounds().height, view, obstacles, NPCs, FloorNumber, isTalking);
    if (player.getPosition().y <= 0.f){
        back_to_town = true;
    }
    if (player.getPosition().y >= backgroundSprite.getGlobalBounds().height){
        next_town = true;
    }
}

void Indoors::draw(sf::RenderWindow& window) {
    sf::FloatRect viewRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height);
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

    for (NPC& npc : NPCs) {
            window.draw(npc);
            if (isTalking && (&npc == npcThatWasTalking)) {
                npc.sendMessage(window, viewRect, font, npc.getDialogue()[currentMessage]);
            }
        }

    // Afficher la fenêtre
    window.display();
}

GameState* Indoors::getNextState() {
    if (back_to_town){
        back_to_town = false;
        music.stop();
        return new Indoors(window, "CROUS", 840, 740, has_key);
    }
    if (next_town){
        next_town = false;
        music.stop();
        return new InGame(window, sf::Vector2u(0,0), sf::Vector2u(3,3), sf::Vector2u(16,16), 0);
    }
    if (kitchen){
        kitchen = false;
        music.stop();
        return new Indoors(window, "KITCHEN", 10, 120, has_key);
    }
    return nullptr;
}
