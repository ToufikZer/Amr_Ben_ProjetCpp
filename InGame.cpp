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
      currentMessage(0) {
        std::cout << "je suis dans game" << std::endl;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    const int level[] = {
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
    };

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

void InGame::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
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
}

void InGame::update(sf::Time deltaTime) {
    player.update(deltaTime, map, view, nullptr, NPCs, isTalking);
    sf::FloatRect viewRect(0, 0, window.getSize().x, window.getSize().y);
    for (NPC& npc : NPCs) {
        npc.update(player, deltaTime, map, nullptr);
        if (isTalking && (&npc == npcThatWasTalking)) {
            npc.sendMessage(window, viewRect, font, npc.getDialogue()[currentMessage]);
        }
    }
}

void InGame::draw() {
    window.clear();
    window.draw(map);
    window.draw(player);
    for (const NPC& npc : NPCs) {
        window.draw(npc);
    }
    window.display();
}