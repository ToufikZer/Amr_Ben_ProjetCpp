// InGame.cpp
#include "InGame.hpp"
#include "iostream"

InGame::InGame(sf::RenderWindow& window)
    : window(window),
      map(sf::Vector2u(16, 16)),
      player("texture/texture_char/char_tileset.png", 2, 3),
      view(sf::Vector2f(player.getPosition().x + 16.f, player.getPosition().y + 16.f), sf::Vector2f(300, 300)),
      isTalking(false),
      npcThatWasTalking(nullptr),
      currentMessage(0),
      level{
        0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
        0,1,1,1,1,1,1,0,0,0,0,2,0,0,0,0,
        1,1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,
        0,1,0,0,2,3,3,3,3,0,1,1,1,0,0,0, // modem limeaire idéoriginel
        0,1,1,0,3,3,3,0,0,0,1,1,1,2,0,0,
        0,0,1,0,3,0,2,2,0,0,1,1,1,1,2,0,
        2,0,1,0,3,0,2,2,2,0,1,1,1,1,1,1,
        0,0,1,0,3,2,2,2,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,0,0,0,0,2,0,0,0,0,
        1,1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,
        0,1,0,0,2,0,3,3,3,0,1,1,1,0,0,0,
        0,1,1,0,3,3,3,0,0,0,1,1,1,2,0,0,
        0,0,1,0,3,0,2,2,0,0,1,1,1,1,2,0,
        2,0,1,0,3,0,2,2,2,0,1,1,1,1,1,1,
        0,0,1,0,3,2,2,2,0,0,0,0,1,1,1,1,
    } {
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    
    if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(32.f, 32.f), level, map.getWidth(), map.getHeight())) {
        std::cerr << "Erreur lors du chargement de la carte" << std::endl;
        std::exit(-1);
    }

    NPCs.push_back(NPC("texture/texture_npc/npcpkmn.png", 5, 3, {"Salut", "test", "caca"}));
    NPCs.push_back(NPC("texture/texture_npc/npcpkmn.png", 0, 8, {"Salut2", "pioupiou", "hello!"}));

    initialize();
}

void InGame::initialize() {
    window.setKeyRepeatEnabled(false);
    npcThatWasTalking = nullptr;
}

void InGame::handleEvent(sf::Event& event, sf::RenderWindow& window) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A) {
                for (NPC& npc : NPCs) {
                    if (!isTalking && player.is_looking_at(npc)) {
                        isTalking = true;
                        npc.setIsTalking(true);
                        npc.update(player, sf::Time::Zero, map, nullptr);
                        npcThatWasTalking = &npc;
                        break;
                    } else if ((&npc == npcThatWasTalking) && isTalking && (currentMessage < npc.getDialogue().size() - 1)) {
                        currentMessage += 1;
                        break;
                    } else {
                        if (npcThatWasTalking != nullptr) {
                            if (&npc == npcThatWasTalking) {
                                isTalking = false;
                                currentMessage = 0;
                                npcThatWasTalking->setIsTalking(false);
                            }
                        }
                    }
                }
            } else if (event.key.code == sf::Keyboard::P) {
                window.setSize(sf::Vector2u(800, 600));
                initialize(); // Réinitialiser l'état après le changement de taille
            }
        }
    }

void InGame::update(sf::Time deltaTime,sf::RenderWindow& window) {
    player.update(deltaTime, map, view, level, NPCs, isTalking);
    for (NPC& npc : NPCs) {
        npc.update(player, deltaTime, map, level);
        //std::cout << isTalking << std::endl; 
    }
}

void InGame::draw(sf::RenderWindow& window) {
    sf::FloatRect viewRect(0, 0, window.getSize().x, window.getSize().y);
    window.clear();
    window.draw(map);
    window.draw(player);
    for (NPC& npc : NPCs) {
        window.draw(npc);
        if (isTalking && (&npc == npcThatWasTalking)) {
            npc.sendMessage(window, viewRect, font, npc.getDialogue()[currentMessage]);
        }
    }
    window.display();
}