// InGame.cpp
#include "InGame.hpp"
#include "iostream"

unsigned int tile_size_ingame = TILESIZE;
float ftile_size_ingame = static_cast<float>(TILESIZE);

InGame::InGame(sf::RenderWindow& window): window(window){

}

InGame::InGame(sf::RenderWindow& window, sf::Vector2u currentmap, sf::Vector2f pos_player, sf::Vector2u map_dimension, Inventory inventaire, unsigned int player_direction)
    : window(window),
      maps(),
      player("texture/texture_char/player_sheet.png", pos_player.x, pos_player.y, player_direction, inventaire),
      map(map_dimension),
      view(sf::Vector2f(player.getPosition().x + 16.f, player.getPosition().y + 16.f), sf::Vector2f(300, 300)),
      isTalking(false),
      npcThatWasTalking(nullptr),
      currentMessage(0),
      in_house(false),
      backmenu(false)
{
    view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    maps.setCurrentMap(currentmap);
    MusicPath = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getMusicPath();
    level = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getLevel();
    NPCs = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getNPCs();
    obstacles = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getObstacles();

    initialize();
}

void InGame::initialize() {
    if (!music.openFromFile(MusicPath)) {
        std::cerr << "Erreur lors du chargement du son" << std::endl;
        std::exit(-1);
    }
    music.setVolume(5);
    music.setLoop(true);
    music.play();

    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(ftile_size_ingame, ftile_size_ingame), level)) {
        std::cerr << "Erreur lors du chargement de la carte" << std::endl;
        std::exit(-1);
    }

    // if (!buffer_bump.loadFromFile("sound/sound/bump.wav")) {
    //     std::cerr << "Failed to load bump sound buffer!" << std::endl;
    //     // Gestion de l'erreur, peut-être lancer une exception ou gérer autrement.
    // }
}


void InGame::handleEvent(sf::Event& event, sf::RenderWindow& window) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A) {
                if (npcThatWasTalking!=nullptr) executeOption();
                for (NPC& npc : NPCs) {
                    if (!isTalking && player.is_looking_at(npc)) {
                        first_dialogue = npc.getDialogue();
                        npc.play_voice();
                        isTalking = true;
                        npc.setIsTalking(true);
                        npc.update(player, sf::Time::Zero, map.getWidth(), map.getHeight(), level, NPCs, obstacles);
                        npcThatWasTalking = &npc;
                        break;
                    } else if ((&npc == npcThatWasTalking) && isTalking && (currentMessage < npc.getDialogue().size() - 1))
                    {
                        npc.stop_voice();
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
                                npc.getDialogue() = first_dialogue;
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
                backmenu = true;
            }

            if (event.key.code == sf::Keyboard::E) {
                EnterHouseUp();
                EnterHouseDown();
            }

            if (event.key.code == sf::Keyboard::J) {
                labyrinthe = true;
            }

            if (event.key.code == sf::Keyboard::Down) {
                if (npcThatWasTalking!=nullptr && npcThatWasTalking->getIsAsking()){
                    if(npcThatWasTalking->getCurrentAnswer() == npcThatWasTalking->getAnswerVector().size()-1) {}
                    else {
                        npcThatWasTalking->setCurrentAnswer(npcThatWasTalking->getCurrentAnswer() + 1);
                    }
                }
            }
            if (event.key.code == sf::Keyboard::Up) {
                if (npcThatWasTalking!=nullptr && npcThatWasTalking->getIsAsking()){
                    if(npcThatWasTalking->getCurrentAnswer() == 0){}
                    else{
                        npcThatWasTalking->setCurrentAnswer(npcThatWasTalking->getCurrentAnswer() - 1);
                    }
                }
            }
            if (event.key.code == sf::Keyboard::S) {
                if (npcThatWasTalking!=nullptr && npcThatWasTalking->getIsAsking()){
                    if(npcThatWasTalking->getCurrentAnswer() == npcThatWasTalking->getAnswerVector().size()-1) {}
                    else {
                        npcThatWasTalking->setCurrentAnswer(npcThatWasTalking->getCurrentAnswer() + 1);
                    }
                }
            }
            if (event.key.code == sf::Keyboard::Z) {
                if (npcThatWasTalking!=nullptr && npcThatWasTalking->getIsAsking()){
                    if(npcThatWasTalking->getCurrentAnswer() == 0){}
                    else{
                        npcThatWasTalking->setCurrentAnswer(npcThatWasTalking->getCurrentAnswer() - 1);
                    }
                }
            }
                      
        }
        // if (event.type == sf::Event::MouseButtonPressed)
        // {
        //     if (event.mouseButton.button == sf::Mouse::Left)
        //     {
        //         if (yesText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
        //         {
        //             backmenu = true;
        //         }
        //         if (cancelText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
        //         {
        //             escape_menu = false;
        //         }
        //     }
        // }
    }



void InGame::update(sf::Time deltaTime,sf::RenderWindow& window) {
    player.update(deltaTime, map, view, level, NPCs, obstacles, isTalking);
    // if (player.getWallColl()) 
    //     {
    //     player.setWallColl(false);
    //     bump_sound.setBuffer(buffer_bump);
    //     bump_sound.setVolume(7);
    //     bump_sound.play();
    //     }
    for (NPC& npc : NPCs) {
        npc.update(player, deltaTime, map.getWidth(), map.getHeight(), level, NPCs, obstacles);
        CheckChangeMap(player.getCurrentPos());
    }

    for (Obstacle& obstacle : obstacles) {
        obstacle.update(player, deltaTime);
    }

    }


void InGame::draw(sf::RenderWindow& window, sf::Event& event) {
    sf::FloatRect viewRect(0, 0, window.getSize().x, window.getSize().y);
    window.clear();
    window.setView(view);
    window.draw(map);
    window.draw(player);
    player.drawInventory(window, font, view);
        for (NPC& npc : NPCs) {
            window.draw(npc);
            if (isTalking && (&npc == npcThatWasTalking)) {
                npc.sendMessage(window, event, viewRect, font, currentMessage);
            }
        }

        for (Obstacle& obstacle : obstacles) {
            window.draw(obstacle);
        }
    // player.drawInteractText(window, font);

    window.display();
}

 GameState* InGame::getNextState(){
    if(backmenu){
        backmenu = false;
        music.stop( );
        return new MainMenu(window, Save("InGame", sf::Vector2f(player.getPosition().x / 32, player.getPosition().y / 32),maps.getCurrentMap(), sf::Vector2u(map.getWidth(), map.getHeight()), player.inventaire, true));
    }
    if(labyrinthe){
        labyrinthe = false;
        music.stop( );
        player.ResetNbPas();
        std::cout << player.getNbPas() << std::endl;
        return new Labyrinthe(window, 0, sf::Vector2f(15,10), sf::Vector2u(31,21), player.inventaire, 3);
    }
    if(in_house){
        music.stop();
        in_house = false;
        if (obstacleInteracting != nullptr) {
            if (obstacleInteracting->getId() != 0){
                if (obstacleInteracting->getId() == 1) return new Indoors(window, "CROUS", 64.f, 140.f, player.inventaire);
                if (obstacleInteracting->getId() == 2) return new InGame(window, sf::Vector2u(0,2), sf::Vector2f(10,7), sf::Vector2u(16,16), player.inventaire, 3);
                if (obstacleInteracting->getId() == 3) return new FraudeGameplay(window, Save("InGame", sf::Vector2f(player.getCurrentPos().x, player.getCurrentPos().y), maps.getCurrentMap(), sf::Vector2u(map.getWidth(), map.getHeight()), player.inventaire, true), player.inventaire);
            }
        }
        else std::cerr << "error obstacle interacting is NULL" << std::endl;
    }
    return nullptr;
}



void InGame::CheckChangeMap(sf::Vector2u position){
        if (player.getChangeMap()== 1){
            player.setChangeMap(0);
            player.setCurrentPos(sf::Vector2u (map.getWidth() - position.x - 1, position.y));
            player.setPosition(ftile_size_ingame*player.getCurrentPos().x , ftile_size_ingame*player.getCurrentPos().y);
            // view.setCenter(player.getPosition().x + 16.f, player.getPosition().y+ 16.f);

            maps.setPreviousCurrentMap();
            MusicPath = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getMusicPath();
            level = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getLevel();
            NPCs = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getNPCs();
            obstacles = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getObstacles();

            if (!music.openFromFile(MusicPath)){ 
                std::cerr << "Erreur lors du chargement du son" << std::endl;
                std::exit(-1);
            }
            music.stop();
            music.setVolume(5);
            music.setLoop(true);
            music.play();  

            if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(ftile_size_ingame, ftile_size_ingame), level)) {
                std::cerr << "Erreur lors du chargement de la carte" << std::endl;
                std::exit(-1);
            }

        }
        if (player.getChangeMap()== 3){
            player.setChangeMap(0);
            player.setCurrentPos(sf::Vector2u (map.getWidth() - position.x - 1, position.y));
            player.setPosition(ftile_size_ingame*player.getCurrentPos().x , ftile_size_ingame*player.getCurrentPos().y);
            // view.setCenter(player.getPosition().x + 16.f, player.getPosition().y+ 16.f);

            maps.setNextCurrentMap();
            MusicPath = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getMusicPath();
            level = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getLevel();
            NPCs = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getNPCs();
            obstacles = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getObstacles();

            if (!music.openFromFile(MusicPath)){ 
                std::cerr << "Erreur lors du chargement du son" << std::endl;
                std::exit(-1);
            }
            music.stop();
            music.setVolume(5);
            music.setLoop(true);
            music.play();

            if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(ftile_size_ingame, ftile_size_ingame), level)) {
                std::cerr << "Erreur lors du chargement de la carte" << std::endl;
                std::exit(-1);
            }
        }

        if (player.getChangeMap()== 2){
            player.setChangeMap(0);
            player.setCurrentPos(sf::Vector2u (position.x, map.getHeight() - position.y - 1));
            player.setPosition(ftile_size_ingame*player.getCurrentPos().x , ftile_size_ingame*player.getCurrentPos().y);
            // view.setCenter(player.getPosition().x + 16.f, player.getPosition().y+ 16.f);

            maps.setUpCurrentMap();
            MusicPath = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getMusicPath();
            level = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getLevel();
            NPCs = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getNPCs();
            obstacles = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getObstacles();

            if (!music.openFromFile(MusicPath)){ 
                std::cerr << "Erreur lors du chargement du son" << std::endl;
                std::exit(-1);
            }
            music.stop();
            music.setVolume(5);
            music.setLoop(true);
            music.play();  

            if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(ftile_size_ingame, ftile_size_ingame), level)) {
                std::cerr << "Erreur lors du chargement de la carte" << std::endl;
                std::exit(-1);
            }

        }
        if (player.getChangeMap()== 4){
            player.setChangeMap(0);
            player.setCurrentPos(sf::Vector2u (position.x, map.getHeight() - position.y - 1));
            player.setPosition(ftile_size_ingame*player.getCurrentPos().x , ftile_size_ingame*player.getCurrentPos().y);
            // view.setCenter(player.getPosition().x + 16.f, player.getPosition().y+ 16.f);

            maps.setDownCurrentMap();
            MusicPath = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getMusicPath();
            level = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getLevel();
            NPCs = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getNPCs();
            obstacles = maps.getMapMap()[maps.getCurrentMap().x][maps.getCurrentMap().y].getObstacles();

            if (!music.openFromFile(MusicPath)){ 
                std::cerr << "Erreur lors du chargement du son" << std::endl;
                std::exit(-1);
            }
            music.stop();
            music.setVolume(5);
            music.setLoop(true);
            music.play();

            if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(ftile_size_ingame, ftile_size_ingame), level)) {
                std::cerr << "Erreur lors du chargement de la carte" << std::endl;
                std::exit(-1);
            }
        }
    // }
}

void InGame::EnterHouseUp(){
    for (Obstacle& obstacle : obstacles) {
                    if (obstacle.getCanEnter() && obstacle.getDirection() == 2){
                        obstacleInteracting = &obstacle;
                        obstacle.setCanEnter(false);
                        in_house = true;
                        break;
                    }
                }
}

void InGame::EnterHouseDown(){
    for (Obstacle& obstacle : obstacles) {
                    if (obstacle.getCanEnter() && obstacle.getDirection() == 3){
                        obstacleInteracting = &obstacle;
                        obstacle.setCanEnter(false);
                        in_house = true;
                        break;
                    }
                }
}

void InGame::executeOption(){
    if (npcThatWasTalking->getIsAsking()){
        std::vector<std::string>& dialogue = npcThatWasTalking->getDialogue();
        std::vector<std::string> answers = npcThatWasTalking->getAnswerVector()[npcThatWasTalking->getCurrentAnswer()].getText();
        dialogue.insert(dialogue.end(), answers.begin(), answers.end());
    }
}
