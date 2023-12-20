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
      currentMessage(0),
      backmenu(false)
      {
      
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
    // sf::Thread thread(&NPC::play_voice);
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A) {
                for (NPC& npc : NPCs) {
                        float pitch = 100;
                    if (!isTalking && player.is_looking_at(npc)) {
                        npc.play_voice();
                        isTalking = true;
                        npc.setIsTalking(true);
                        npc.update(player, sf::Time::Zero, map.getWidth(), map.getHeight(), level, NPCs);
                        npcThatWasTalking = &npc;
                        break;
                    } else if ((&npc == npcThatWasTalking) && isTalking && (currentMessage < npc.getDialogue().size() - 1))
                    {
                        npc.play_voice();
                        currentMessage += 1;
                        if (currentMessage == npc.getDialogue().size()){
                                npc.setPlayBool(false);
                                npc.play_voice();
                        }
                        break;
                    } else {
                        if (npcThatWasTalking != nullptr) {
                            if (&npc == npcThatWasTalking) {
                                npc.setPlayBool(true);
                                npc.getDelay() = 0;
                                isTalking = false;
                                currentMessage = 0;
                                npcThatWasTalking->setIsTalking(false);
                            }
                        }
                    }
                }
            }
            if (event.key.code == sf::Keyboard::Escape) {
                escape_menu = true;
            }
            // if (event.key.code == sf::Keyboard::R) {
            //     //window.clear();
            //     backmenu = true;
            //     }           
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (yesText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                {
                    backmenu = true;
                }
                if (cancelText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                {
                    escape_menu = false;
                }
            }
        }
    }



void InGame::update(sf::Time deltaTime,sf::RenderWindow& window) {
    if (!escape_menu)
    {
    player.update(deltaTime, map.getWidth(), map.getHeight(), view, level, NPCs, isTalking);
    for (NPC& npc : NPCs) {
        npc.update(player, deltaTime, map.getWidth(), map.getHeight(), level, NPCs);
        CheckChangeMap(player.getCurrentPos());
    }
    }
    if (escape_menu) 
    {
        drawConfirmationWindow(window);
        Detect_Yes(window);
        Detect_Cancel(window);
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

    if (escape_menu) {
    window.draw(back_menu);
    window.draw(question);
    window.draw(yesText);
    window.draw(cancelText);
    window.draw(line);
    }
    window.display();
}

// PROBLEME DE SEG FAULT

GameState* InGame::getNextState(){
    if(backmenu){
        backmenu = false;
        escape_menu = false;
        for(int i = 1; i < 100000; i++)
        {
            maps.getMusic().setVolume(1 - i/100000);
        }
        maps.getMusic().stop();
        return new MainMenu(window);
    }
    return nullptr;
}



void InGame::CheckChangeMap(sf::Vector2u position){
    // for (sf::Vector2u tile : maps.getChangeTile()){
        // std::cout << player.getChangeMap() << std::endl;
        if (player.getChangeMap()== 1){
            player.setChangeMap(0);
            player.setCurrentPos(sf::Vector2u (map.getWidth() - position.x - 1, position.y));
            player.setPosition(32.f*player.getCurrentPos().x , 32.f*player.getCurrentPos().y);
            // std::cout << player.getCurrentPos().x << ";" << player.getCurrentPos().y << std::endl;
        
            maps.setMap_map2();
            level = maps.getLevel();
            NPCs = maps.getNPCs();
            if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(32.f, 32.f), level)) {
                std::cerr << "Erreur lors du chargement de la carte" << std::endl;
                std::exit(-1);
            }
        }
        if (player.getChangeMap()== 3){
            player.setChangeMap(0);
            player.setCurrentPos(sf::Vector2u (map.getWidth() - position.x - 1, position.y));
            player.setPosition(32.f*player.getCurrentPos().x , 32.f*player.getCurrentPos().y);
            maps.setMap_map1();
            level = maps.getLevel();
            NPCs = maps.getNPCs();
            if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(32.f, 32.f), level)) {
                std::cerr << "Erreur lors du chargement de la carte" << std::endl;
                std::exit(-1);
            }
        }
    // }
}

void InGame::drawConfirmationWindow(sf::RenderWindow& window) {
    back_menu.setSize(sf::Vector2f(300.f, 125.f));
    back_menu.setPosition(100.f, 148.f);
    back_menu.setFillColor(sf::Color(0, 0, 0, 150)); 

    question.setString("Do you want to leave?");
    question.setFont(font);
    question.setCharacterSize(20);
    question.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = question.getLocalBounds();
    question.setPosition(250.f - textBounds.width / 2.f, 178.f - textBounds.height / 2.f);

    yesText.setString("Yes");
    yesText.setFont(font);
    ResetYes();

    cancelText.setString("Cancel");
    cancelText.setFont(font);
    ResetCancel();

    line.setSize(sf::Vector2f(2.f, 78.f));
    line.setPosition(250.f, 200.f);
    line.setFillColor(sf::Color(0, 0, 0, 250));

    // Dessiner les éléments sur la fenêtre
}

void InGame::HighlightCancel(){
    cancelText.setCharacterSize(25);
    cancelText.setFillColor(sf::Color::Red);
    cancelText.setPosition(280.f , 215.f);
}

void InGame::ResetCancel(){
    cancelText.setCharacterSize(20);
    cancelText.setPosition(280.f , 220.f);
    cancelText.setFillColor(sf::Color::White);
}

void InGame::HighlightYes(){
    yesText.setCharacterSize(25);
    yesText.setFillColor(sf::Color::Green);
    yesText.setPosition(170.f, 215.f);
}

void InGame::ResetYes(){
    yesText.setCharacterSize(20);
    yesText.setPosition(170.f, 220.f);
    yesText.setFillColor(sf::Color::White);
}

void InGame::Detect_Yes(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (yesText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        HighlightYes();
    }
    else{
        ResetYes();
    }
}

void InGame::Detect_Cancel(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (cancelText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {   
        HighlightCancel();
    }
    else{
        ResetCancel();
    }
}