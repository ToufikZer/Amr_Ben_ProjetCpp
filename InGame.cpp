// InGame.cpp
#include "InGame.hpp"
#include "iostream"

InGame::InGame(sf::RenderWindow& window)
    : window(window),
      map(sf::Vector2u(16, 16)),
      maps(),
      player("texture/texture_char/char_tileset.png", 2, 3),
      view(sf::Vector2f(player.getPosition().x + 16.f, player.getPosition().y + 16.f), sf::Vector2f(300, 300)),
      isTalking(false),
      npcThatWasTalking(nullptr),
      currentMessage(0){
      maps.setMap_map1();
      level = maps.getLevel();
      NPCs = maps.getNPCs();

    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    
    if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(32.f, 32.f), level)) {
        std::cerr << "Erreur lors du chargement de la carte" << std::endl;
        std::exit(-1);
    }

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
                        npc.update(player, sf::Time::Zero, map.getWidth(), map.getHeight(), level);
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
            }
            if (event.key.code == sf::Keyboard::P) {
                window.create(sf::VideoMode(512, 512), "JO Tourismo");
                window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.25,sf::VideoMode::getDesktopMode().height * 0.20 ));
            }
            if (event.key.code == sf::Keyboard::R) {
                //window.clear();
                maps.setMap_map2();
                level = maps.getLevel();
                NPCs = maps.getNPCs();
                if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(32.f, 32.f), level)) {
                std::cerr << "Erreur lors du chargement de la carte" << std::endl;
                std::exit(-1);
    }
            }
        }
    }

void InGame::update(sf::Time deltaTime,sf::RenderWindow& window) {
    player.update(deltaTime, map.getWidth(), map.getHeight(), view, level, NPCs, isTalking);
    for (NPC& npc : NPCs) {
        npc.update(player, deltaTime, map.getWidth(), map.getHeight(), level);
        CheckChangeMap(player.getCurrentPos());
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

void InGame::CheckChangeMap(sf::Vector2u position){
    for (sf::Vector2u tile : maps.getChangeTile()){
        if (position.x == tile.x && position.y == tile.y){
            maps.setMap_map2();
            level = maps.getLevel();
            NPCs = maps.getNPCs();
            if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(32.f, 32.f), level)) {
                std::cerr << "Erreur lors du chargement de la carte" << std::endl;
                std::exit(-1);
        }
    }
}
}