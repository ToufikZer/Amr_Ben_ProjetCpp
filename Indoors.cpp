// InDoors.cpp
#include "Indoors.hpp"
#include "PlayerIndoors.hpp"
#include "MapInstances.hpp"
#include <iostream>

MapIndoors GARE = MAP5;
MapIndoors ROOM = MAP6;
MapIndoors CROUS = MAP7;
MapIndoors KITCHEN = MAP8;
MapIndoors AIRPORT = MAP9;
MapIndoors CONCESS = MAP10;
Item keyRoom = Item("Key","Une clé de chambre", 1, "texture/texture_item/key.png");
Item KitchenKnife = Item("KitchenKnife", "Un couteau de cuisine banal", 2, "texture/texture_item/zanpakuto.png");
Item Zanpakuto = Item("Zanpakuto", "Decoupe Mokhtar", 2, "texture/texture_item/knife.png");
Item Bottes = Item("Bottes", "Cours Forest", 0, "texture/texture_item/bottes.png");

Indoors::Indoors(sf::RenderWindow& window, std::string MapName, float pos_player_x, float pos_player_y, Inventory inventaire, std::string objectif_text, bool combat_win)
    : window(window),
      objectif_text(objectif_text),
      player("texture/texture_char/new_player2.png", pos_player_x, pos_player_y, inventaire),
      MapName(MapName),
      enigme(Enigme()),
      isTalking(false),
      npcThatWasTalking(nullptr),
      currentMessage(0),
      back_to_town(false),
      backmenu(false),
      next_town(false),
      kitchen(false),
      exit_concess(false),
      car(false),
      crous(false),
      room(false),
      exit_room(false),
      bagarre(false),
      exit_gare(false),
      combat_win(combat_win),
      enigme_active(false)
{
    MapList.push_back(GARE);
    MapList.push_back(ROOM);
    MapList.push_back(CROUS);
    MapList.push_back(KITCHEN);
    MapList.push_back(AIRPORT);
    MapList.push_back(CONCESS);

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

    // if (!music.openFromFile(MusicPath)) {
    //     std::cerr << "Erreur lors du chargement du son" << std::endl;
    //     std::exit(-1);
    // }

    // music.setVolume(5);
    // music.setLoop(true);
    // music.play();
    if (!backgroundTexture.loadFromFile(BackgroundPath)) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    player.setSpeed(PlayerSpeed);
    view.reset(sf::FloatRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height));
    objectif.setPosition(sf::Vector2f(backgroundSprite.getGlobalBounds().width * 0.39, backgroundSprite.getGlobalBounds().height*0.02));
    objectif.setCharacterSize(backgroundSprite.getGlobalBounds().height*0.05);
    objectif.setFillColor(sf::Color::Black);
    objectif.setStyle(sf::Text::Bold);
    objectif.setFont(font);
    objectif.setString(objectif_text);
}

void Indoors::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            if (npcThatWasTalking!=nullptr) executeOption();
            for (NPC& npc : NPCs) {
                if (player.collision_NPCs(sf::Vector2f(player.getPosition().x,player.getPosition().y), npc)) {
                    if (npc.getDialogue()[currentMessage] == "EXIT") {
                        back_to_town = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "EXITCONCESS") {
                        exit_concess = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "EXITROOM") {
                        exit_room = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "EXITGARE") {
                        exit_gare = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "CUISINE"){
                        kitchen = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "CAR"){
                        if (player.getInventory().getMoney() >= 300) car = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "BATS TOI"){
                        bagarre = true;
                    }
                    else if (has_key(player.getInventory()) && npc.getDialogue()[currentMessage] == "Oh, the doors seems to be half-open"){
                        room = true;
                    }
                    
                    else if (npc.getDialogue()[currentMessage] == "KEY"){
                        first_dialogue = npc.getDialogue();
                        if (!has_key(player.getInventory())){
                        isTalking = true;
                        player.getInventory().addItem(keyRoom);
                        npc.setIsTalking(true);
                        npcThatWasTalking = &npc;
                        currentMessage += 1;
                        break;
                        }
                        else {}
                    }
                    else if (npc.getDialogue()[currentMessage] == "ENIGME1"){
                        if(!enigme1_done){
                            enigme_active = true;
                            npcThatWasTalking = nullptr;
                            enigme = Enigme("Si j'ai 3 pommes et que Charles en a 5, \ncombien a-t-on de pommes ?", 8, font, 0);
                            isTalking = true;
                            currentMessage = 0;
                            break;
                        }
                    }
                    else if (npc.getDialogue()[currentMessage] == "KNIFE"){
                        first_dialogue = npc.getDialogue();
                        if (!has_kitchen_knife(player.getInventory())){
                            isTalking = true;
                            player.getInventory().addItem(Zanpakuto);
                            npc.setIsTalking(true);
                            npcThatWasTalking = &npc;
                            currentMessage += 1;
                            break;
                        }
                        else {}
                    }
                    else if (npc.getDialogue()[currentMessage] == "BOTTES"){
                        first_dialogue = npc.getDialogue();
                        if (!has_boots(player.getInventory())){
                            isTalking = true;
                            player.getInventory().addItem(Bottes);
                            npc.setIsTalking(true);
                            npcThatWasTalking = &npc;
                            currentMessage += 1;
                            break;
                        }
                        else {}
                    }
                    else{
                        if (!isTalking){
                            first_dialogue = npc.getDialogue();
                            if (npc.getTexturePath() == "texture/texture_npc/door_invisible.png") npc.play_toctoc();
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
                                    npc.getDialogue() = first_dialogue;
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
        if (event.key.code == sf::Keyboard::Up)
        {
            if (npcThatWasTalking!=nullptr && npcThatWasTalking->getIsAsking()){
                if(npcThatWasTalking->getCurrentAnswer() == 0){}
                else{
                    npcThatWasTalking->setCurrentAnswer(npcThatWasTalking->getCurrentAnswer() - 1);
                }
            }
        }
        if (event.key.code == sf::Keyboard::Down)
        {
            if (npcThatWasTalking!=nullptr && npcThatWasTalking->getIsAsking()){
                if(npcThatWasTalking->getCurrentAnswer() == npcThatWasTalking->getAnswerVector().size()-1) {}
                else {
                    npcThatWasTalking->setCurrentAnswer(npcThatWasTalking->getCurrentAnswer() + 1);
                }
            }
        }
        if (event.key.code == sf::Keyboard::S)
        {
            if (npcThatWasTalking!=nullptr && npcThatWasTalking->getIsAsking()){
                if(npcThatWasTalking->getCurrentAnswer() == npcThatWasTalking->getAnswerVector().size()-1) {}
                else {
                    npcThatWasTalking->setCurrentAnswer(npcThatWasTalking->getCurrentAnswer() + 1);
                }
            }
        }
        if (event.key.code == sf::Keyboard::Z)
        {
            if (npcThatWasTalking!=nullptr && npcThatWasTalking->getIsAsking()){
                if(npcThatWasTalking->getCurrentAnswer() == 0) {}
                else {
                    npcThatWasTalking->setCurrentAnswer(npcThatWasTalking->getCurrentAnswer() - 1);
                }
            }
        }
        if (event.key.code == sf::Keyboard::Escape) {
                backmenu = true;
            }
    }
    if (event.type == sf::Event::TextEntered) {
        if (enigme_active) {
            if (event.text.unicode == 8) {
                enigme.supprimerCaractere();
            } 
            else if (event.text.unicode == 13) {
                if (enigme.verifierReponse()) {
                    player.getInventory().WinMoney();
                    if (enigme.getId() == 0) enigme1_done = true;

                } 
                enigme_active = false;
                isTalking = false;
            } 
            else if (event.text.unicode < 48 || event.text.unicode > 57) {

            } 
            else {
                enigme.ajouterCaractere(event.text.unicode);
            }
        }
    }
}

void Indoors::update(sf::Time deltaTime, sf::RenderWindow& window) {
    player.update(deltaTime, font, backgroundSprite.getGlobalBounds().width,
                  backgroundSprite.getGlobalBounds().height, view, obstacles, NPCs, FloorNumber, isTalking);
    if (player.getPosition().y <= 0.f){
        crous = true;
    }
    if (player.getPosition().y >= backgroundSprite.getGlobalBounds().height){
        next_town = true;
    }
}

void Indoors::draw(sf::RenderWindow& window, sf::Event& event) {
    sf::FloatRect viewRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height);
    // Effacer la fenêtre
    window.clear();

    window.draw(backgroundSprite);

    // Définir la vue
    window.setView(view);
    // Dessiner le joueur


    for (Obstacle& obstacle : obstacles){
        window.draw(obstacle);
    }

    window.draw(player);
    for (NPC& npc : NPCs) {
            if (npc.getDialogue()[0] == "KEY" && has_key(player.getInventory())){} //On pourrait faire une fonction draw_key avec la meme condition mais pg la
            else{
                window.draw(npc);
            }
            if (isTalking && (&npc == npcThatWasTalking)) {
                npc.sendMessage(window, event, viewRect, font, currentMessage);
            }
        }
    sf::FloatRect globalBounds = objectif.getGlobalBounds();
    sf::RectangleShape boundingBox(sf::Vector2f(globalBounds.width + 10, globalBounds.height + 10));
    boundingBox.setPosition(globalBounds.left - 5, globalBounds.top - 5);
    boundingBox.setOutlineColor(sf::Color(139, 69, 19));
    boundingBox.setOutlineThickness(globalBounds.width * 0.01);
    window.draw(boundingBox);
    window.draw(objectif);
    player.drawInventory(window, font, view);
    if (enigme_active) {
        enigme.setPosition(50,50);
        enigme.setSize(400,200);
        enigme.afficher(window);
    }
    // player.drawInteractText(window, font);
    // Afficher la fenêtre
    window.display();
}

GameState* Indoors::getNextState() {
    if(backmenu){
        backmenu = false;
        return new MainMenu(window, Save("InDoors", player.getPosition(), MapName, player.getInventory(), true, combat_win));
    }
    if (back_to_town){
        back_to_town = false;
        if(combat_win) return new InGame(window, sf::Vector2u(0,3), sf::Vector2f(10,7), sf::Vector2u(16,16), player.getInventory(), 3, "Se rendre a la gare", combat_win);
        else return new InGame(window, sf::Vector2u(0,3), sf::Vector2f(10,7), sf::Vector2u(16,16),player.getInventory(), 0, "Se rendre au CROUS", combat_win);
    }
    if (next_town){
        next_town = false;
        if(combat_win) return new InGame(window, sf::Vector2u(0,0), sf::Vector2f(4,7), sf::Vector2u(16,16),player.getInventory(), 0, "Se rendre a la gare", combat_win);
        else return new InGame(window, sf::Vector2u(0,0), sf::Vector2f(4,7), sf::Vector2u(16,16),player.getInventory(), 0, "Trouver un moyen de se deplacer", combat_win);
    }
    if (crous){
        crous = false;
        return new Indoors(window, "CROUS", 840, 740, player.getInventory(), "Trouver une chambre libre", combat_win);
    }
    if (kitchen){
        kitchen = false;
        return new Indoors(window, "KITCHEN", 20, 160, player.getInventory(), "", combat_win);
    }
    if (exit_concess){
        exit_concess = false;
        if(combat_win) return new InGame(window, sf::Vector2u(0,1), sf::Vector2f(10,7), sf::Vector2u(16,16),player.getInventory(), 0, "Se rendre a la gare", combat_win);
        else return new InGame(window, sf::Vector2u(0,1), sf::Vector2f(10,7), sf::Vector2u(16,16),player.getInventory(), 0, "Acheter un vehicule", combat_win);
    }   
    if (car){
        car = false;
        return new Explication(window, "car", Save("InDoors", player.getPosition(), MapName, player.getInventory(), true, combat_win), "texture/texture_expl/car.png");
    }
    if (room){
        room = false;
        return new Indoors(window, "ROOM", 500, 320, player.getInventory(), "C'est l'heure de la BAGARRE", combat_win);
    }
    if (exit_room){
        exit_room = false;
        if(combat_win) return new Indoors(window, "CROUS", 80, 740, player.getInventory(), "Se rendre a la gare", combat_win);
        else return new Indoors(window, "CROUS", 80, 740, player.getInventory(), "Va prendre ta revanche !", combat_win);
    }
    if (bagarre){
        bagarre = false;
        return new Explication(window, "bagarre", Save("InDoors", player.getPosition(), MapName, player.getInventory(), true, combat_win), "texture/texture_expl/bagarre.png");
    }
    if (exit_gare){
        exit_gare = false;
        return new InGame(window, sf::Vector2u(0,2), sf::Vector2f(6,7), sf::Vector2u(16,16),player.getInventory(), 0, "Aller a la gare", combat_win);
    }
    return nullptr;
}


bool Indoors::has_key(Inventory inventaire){
    for (Item& item : inventaire.getItems()){
        if (item.getName() == "Key") return true;
    }
    return false;
}

bool Indoors::has_kitchen_knife(Inventory inventaire){
    for (Item& item : inventaire.getItems()){
        if (item.getName() == "Zanpakuto") return true;
    }
    return false;
}

bool Indoors::has_boots(Inventory inventaire){
    for (Item& item : inventaire.getItems()){
        if (item.getName() == "Bottes") return true;
    }
    return false;
}


void Indoors::executeOption(){
    if (npcThatWasTalking->getIsAsking()){
        std::vector<std::string>& dialogue = npcThatWasTalking->getDialogue();
        std::vector<std::string> answers = npcThatWasTalking->getAnswerVector()[npcThatWasTalking->getCurrentAnswer()].getText();
        dialogue.insert(dialogue.end(), answers.begin(), answers.end());
    }
}
