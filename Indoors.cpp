//Ce code permet la gestion des différentes parties durant lesquelles le joueur est en intérieur (il s'en passe des choses en intérieur...)
// 


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
MapIndoors STADE = MAP11;
MapIndoors FINAL = MAP12;
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
      enigme_active(false),
      enigme1_done(false),
      enigme2_done(false),
      enigme3_done(false),
      enigme4_done(false),
      fraude(false),
      no_fraude(false),
      labyrinthe(false),
      bagarreFou(false),
      bagarreF(false)
{
    initialize_maplist();

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

    if (!backgroundTexture.loadFromFile(BackgroundPath)) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    player.setSpeed(PlayerSpeed);
    view.reset(sf::FloatRect(0, 0, backgroundSprite.getGlobalBounds().width, backgroundSprite.getGlobalBounds().height));
    initialize_objectif();
}

void Indoors::initialize_maplist(){
    MapList.push_back(GARE);
    MapList.push_back(ROOM);
    MapList.push_back(CROUS);
    MapList.push_back(KITCHEN);
    MapList.push_back(AIRPORT);
    MapList.push_back(CONCESS);
    MapList.push_back(STADE);
    MapList.push_back(FINAL);
}

void Indoors::initialize_objectif(){
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
                    else if (npc.getDialogue()[currentMessage] == "Fraudons!"){
                        fraude = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "CAR"){
                        if (player.getInventory().getMoney() >= 300) car = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "Avez vous assez d'argent?" && (player.getInventory().getMoney() >= 4)){
                        no_fraude = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "BATS TOI"){
                        bagarre = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "PARLE AVEC MOI"){
                        bagarreFou = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "AFFRONTE MOI"){
                        bagarreF = true;
                    }
                    else if (npc.getDialogue()[currentMessage] == "*Vous vous evanouissez brusquement...*"){
                        labyrinthe = true;
                    }
                    else if (has_key(player.getInventory()) && npc.getDialogue()[currentMessage] == "Oh, the doors seems to be half-open"){
                        room = true;
                    }
                    
                    else if (npc.getDialogue()[currentMessage] == "KEY"){
                        first_dialogue = npc.getDialogue();
                        if (!has_key(player.getInventory())){
                            event_key(npc);
                            break;
                        }
                        else {}
                    }
                    else if (npc.getDialogue()[currentMessage] == "KNIFE"){
                        first_dialogue = npc.getDialogue();
                        if (!has_kitchen_knife(player.getInventory())){
                            event_knife(npc);
                            break;
                        }
                        else {}
                    }
                    else if (npc.getDialogue()[currentMessage] == "BOTTES"){
                        first_dialogue = npc.getDialogue();
                        if (!has_boots(player.getInventory())){
                            event_bottes(npc);
                            break;
                        }
                        else {}
                    }

                    else if (npc.getDialogue()[currentMessage] == "ENIGME1"){
                        if(!enigme1_done){
                            event_enigme1();
                            break;
                        }
                    }
                    else if (npc.getDialogue()[currentMessage] == "ENIGME2"){
                        if(!enigme2_done){
                            event_enigme2();
                            break;
                        }
                    }
                    else if (npc.getDialogue()[currentMessage] == "ENIGME3"){
                        if(!enigme3_done){
                            event_enigme3();
                            break;
                        }
                    }
                    else if (npc.getDialogue()[currentMessage] == "ENIGME4"){
                        if(!enigme4_done){
                            event_enigme4();
                            break;
                        }
                    }
                    else{
                        if (!isTalking){
                            FirstTalk(npc);
                            break;
                        }
                        else if ((&npc == npcThatWasTalking) && isTalking && (currentMessage < npc.getDialogue().size() - 1))
                    {
                        currentMessage += 1;
                        break;
                    }
                        else {
                            LastTalk(npc);
                        }
                    }
                }
            }
        }
        ChooseAnswer(event);
        if (event.key.code == sf::Keyboard::Escape) {
                backmenu = true;
            }
    }
    EnigmeAnswer(event);
}

void Indoors::event_key(NPC& npc){
    isTalking = true;
    player.getInventory().addItem(keyRoom);
    npc.setIsTalking(true);
    npcThatWasTalking = &npc;
    currentMessage += 1;
}

void Indoors::event_knife(NPC& npc){
    isTalking = true;
    player.getInventory().addItem(Zanpakuto);
    npc.setIsTalking(true);
    npcThatWasTalking = &npc;
    currentMessage += 1;
}

void Indoors::event_bottes(NPC& npc){
    isTalking = true;
    player.getInventory().addItem(Bottes);
    npc.setIsTalking(true);
    npcThatWasTalking = &npc;
    currentMessage += 1;
}

void Indoors::event_enigme1(){
    enigme_active = true;
    npcThatWasTalking = nullptr;
    enigme = Enigme("Si j'ai 3 pommes et que Charles en a 5,\nSachant que Abdel m'a vendu 2 pommes\nEt que Charles m'en a vole 4\ncombien avais-je de pommes au debut?", 5, font, 0);
    isTalking = true;
    currentMessage = 0;
}

void Indoors::event_enigme2(){
    enigme_active = true;
    npcThatWasTalking = nullptr;
    enigme = Enigme("Voici une enigme:\nUn homme faisant connaissance avec\nsa voisine apprend qu'elle a 3 filles.\nIl demande leurs ages, mais elle ne repond pas\ndirectement elle prefere lui faire deviner:\n-Le produit de leurs ages fait 36; dit-elle\n-Il me faudrait plus d'indices\n-Somme de leurs ages = numero de la maison en face\n-Je ne peux toujours pas trouver\n-L'ainee est blonde\n-Ah oui, c'est bon j'ai trouve !\n\nQuel est l'age de l'ainee ?", 9, font, 1);
    isTalking = true;
    currentMessage = 0;
}

void Indoors::event_enigme3(){
    enigme_active = true;
    npcThatWasTalking = nullptr;
    enigme = Enigme("Trouvez le code secret a 4 chiffres:\nLa somme des 4 chiffres est 13,\nle chiffre des milliers est 2 fois plus\ngrand que celui des unites\nle chiffre des centaines est 3 fois plus\ngrand que celui des dizaines.", 6313, font, 2);
    isTalking = true;
    currentMessage = 0;
}

void Indoors::event_enigme4(){
    enigme_active = true;
    npcThatWasTalking = nullptr;
    enigme = Enigme("Trouvez le code cache dans la phrase suivante:\n\nUn oeuf bien cuit!", 1918, font, 3);
    isTalking = true;
    currentMessage = 0;
}

void Indoors::FirstTalk(NPC& npc){
    first_dialogue = npc.getDialogue();
    if (npc.getTexturePath() == "texture/texture_npc/door_invisible.png") npc.play_toctoc();
    isTalking = true;
    npc.setIsTalking(true);
    npcThatWasTalking = &npc;
}

void Indoors::LastTalk(NPC& npc){
    if (npcThatWasTalking != nullptr) {
        if (&npc == npcThatWasTalking) {
            npc.getDialogue() = first_dialogue;
            isTalking = false;
            currentMessage = 0;
            npcThatWasTalking->setIsTalking(false);
        }
    }
}

void Indoors::ChooseAnswer(sf::Event& event){
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
}

void Indoors::EnigmeAnswer(sf::Event& event){
    if (event.type == sf::Event::TextEntered) {
        if (enigme_active) {
            if (event.text.unicode == 8) {
                enigme.supprimerCaractere();
            } 
            else if (event.text.unicode == 13) {
                if (enigme.verifierReponse()) {
                    player.getInventory().WinMoney();
                    if (enigme.getId() == 0) enigme1_done = true;
                    if (enigme.getId() == 1) enigme2_done = true;
                    if (enigme.getId() == 2) enigme3_done = true;
                    if (enigme.getId() == 3) enigme4_done = true;
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
    window.clear();

    window.draw(backgroundSprite);

    window.setView(view);

    for (Obstacle& obstacle : obstacles){
        window.draw(obstacle);
    }

    for (NPC& npc : NPCs) {
        if (npc.getDialogue()[0] == "KEY" && has_key(player.getInventory())){} 
        else{
            window.draw(npc);
        }
    }
        window.draw(player);
    for (NPC& npc : NPCs) {
            if (isTalking && (&npc == npcThatWasTalking)) {
                npc.sendMessage(window, event, viewRect, font, currentMessage);
            }
        }
    player.drawInventory(window, font, view);
    draw_objectif();
    if (enigme_active) {
        enigme.setPosition(164,264);
        enigme.setSize(738,484);
        enigme.afficher(window);
    }
    window.display();
}

void Indoors::draw_objectif(){
    sf::FloatRect globalBounds = objectif.getGlobalBounds();
    sf::RectangleShape boundingBox(sf::Vector2f(globalBounds.width + 10, globalBounds.height + 10));
    boundingBox.setPosition(globalBounds.left - 5, globalBounds.top - 5);
    boundingBox.setOutlineColor(sf::Color(139, 69, 19));
    boundingBox.setOutlineThickness(globalBounds.width * 0.01);
    window.draw(boundingBox);
    window.draw(objectif);
}

GameState* Indoors::getNextState() {
    if(backmenu){
        backmenu = false;
        return new MainMenu(window, Save("InDoors", player.getPosition(), MapName, player.getInventory(), true, combat_win));
    }
    if (back_to_town){
        back_to_town = false;
        if(combat_win) return new InGame(window, sf::Vector2u(0,2), sf::Vector2f(10,7), sf::Vector2u(16,16), player.getInventory(), 3, "Se rendre a la gare", true);
        else return new InGame(window, sf::Vector2u(0,2), sf::Vector2f(10,7), sf::Vector2u(16,16),player.getInventory(), 0, "Se rendre au CROUS", false);
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
    if (bagarreFou){
        bagarreFou = false;
        return new Bagarre(window, Save("InDoors", player.getPosition(), MapName, player.getInventory(), true, combat_win), player.getInventory(), "texture/texture_decor/2Qpng.png","texture/texture_char/new_player2.png", 15, 50, 400, 3000, 2, false);
    }
    if (exit_gare){
        exit_gare = false;
        return new InGame(window, sf::Vector2u(0,3), sf::Vector2f(6,7), sf::Vector2u(16,16),player.getInventory(), 0, "Aller a la gare", combat_win);
    }
    if (fraude){
        fraude = false;
        return new Explication(window, "fraude", Save("InDoors", player.getPosition(), MapName, player.getInventory(), true, combat_win), "texture/texture_expl/fraude.png");
    }
    if (no_fraude){
        no_fraude = false;
        player.getInventory().setMoney(0);
        return new InGame(window, sf::Vector2u(0,3), sf::Vector2f(9,9), sf::Vector2u(16,16),player.getInventory(), 1, "Aller voir le match", combat_win);
    }
    if(labyrinthe){
        labyrinthe = false;
        return new Explication (window, "lab", Save("InDoors", player.getPosition(), MapName, player.getInventory(), true, combat_win), "texture/texture_expl/lab.png");
    }
    if (bagarreF){
        bagarreF = false;
        return new Explication(window, "bagarre_2", Save("InDoors", player.getPosition(), MapName, player.getInventory(), true, combat_win), "texture/texture_expl/bagarre_2.png");
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
