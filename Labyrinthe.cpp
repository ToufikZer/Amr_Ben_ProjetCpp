    // InGame.cpp
    #include "Labyrinthe.hpp"
    #include "iostream"

    unsigned int tile_size_ingame_lab = TILESIZE;
    float ftile_size_ingame_lab = static_cast<float>(TILESIZE);
    Map Lab = MAP4; 
    Labyrinthe::Labyrinthe(sf::RenderWindow& window): window(window){

    }

    Labyrinthe::Labyrinthe(sf::RenderWindow& window, unsigned int nb_pas, sf::Vector2f pos_player, sf::Vector2u map_dimension, Inventory inventaire, unsigned int player_direction)
        : window(window),
        view(sf::Vector2f(player.getPosition().x + 16.f, player.getPosition().y + 16.f), sf::Vector2f(300, 300)),
        map(map_dimension),
        player("texture/texture_char/player_sheet.png", pos_player.x, pos_player.y, player_direction, inventaire),
        nb_pas(nb_pas),
        light_off(false),
        isTalking(false),
        npcThatWasTalking(nullptr),
        currentMessage(0),
        end_lab(false),
        backmenu(false),
        skip(false)
    {
        player.SetNbPas(nb_pas);
        MusicPath = Lab.getMusicPath();
        level = Lab.getLevel();
        NPCs = Lab.getNPCs();
        obstacles = Lab.getObstacles();

        initialize();
    }

    void Labyrinthe::initialize() {

        if (!font.loadFromFile("font/arial.ttf")) {
            std::cerr << "Erreur lors du chargement de la police" << std::endl;
            std::exit(-1);
        }

        if (!map.load("texture/texture_decor/tileset_lab.png", sf::Vector2u(ftile_size_ingame_lab, ftile_size_ingame_lab), level)) {
            std::cerr << "Erreur lors du chargement de la carte" << std::endl;
            std::exit(-1);
        }
    }


    void Labyrinthe::handleEvent(sf::Event& event, sf::RenderWindow& window) { //inputs joueur
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    restart = true;
                }
                if (event.key.code == sf::Keyboard::K) {
                    skip = true;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    backmenu = true;
                }         
            }
        }



    void Labyrinthe::update(sf::Time deltaTime,sf::RenderWindow& window) { //traitement à chaque frame du jeu
        player.update(deltaTime, map, level, NPCs, obstacles, isTalking);
        
        Trap();
        
        if (player.getChangeMap()== 2){
            player.setChangeMap(0);
            end_lab = true;
        }
        RedTile();
        
        GreenTile();

        YellowTile();

        if (player.getNbPas() > 15) light_off = true;
    }


    void Labyrinthe::draw(sf::RenderWindow& window, sf::Event& event) { //affichage sur l'écran du joueur
        sf::FloatRect viewRect(sf::Vector2f(player.getPosition().x - view.getSize().x / 2, player.getPosition().y - view.getSize().y / 2), sf::Vector2f(300, 300));
        view.reset(viewRect);
        window.clear();
        window.setView(view);
        window.draw(map);
        if (light_off){
            sf::RectangleShape LightOffRect(view.getSize());
            LightOffRect.setPosition(sf::Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2));
            LightOffRect.setFillColor(sf::Color::Black);
            window.draw(LightOffRect);
        }
        window.draw(player);
        player.drawInventory(window, font, view);

        window.display();
    }

    GameState* Labyrinthe::getNextState(){ // indique les différents cas de figure à la fin du jeu (si le joueur gagne, si le joueur perd, si le joueur skip...)
        if(backmenu){
            backmenu = false;
            return new MainMenu(window, Save("Labyrinthe", sf::Vector2f(player.getPosition().x / 32, player.getPosition().y / 32), player.getNbPas(), sf::Vector2u(map.getWidth(), map.getHeight()), player.getInventory(), true, true));
        }
        
        if(skip){
            skip = false;
            return new Indoors(window, "FINAL", 300.f, 125.f, player.getInventory(), "AFFRONTEZ ANNIE!!", true);
        }
        if(restart){
            restart = false;
            return new Labyrinthe(window, 0, sf::Vector2f(15,10), sf::Vector2u(31,21), player.getInventory(), 3);
        }
        if(end_lab){
            end_lab = false;
            return new Indoors(window, "FINAL", 300.f, 125.f, player.getInventory(), "AFFRONTEZ ANNIE!!", true);
        }
        return nullptr;
    }

sf::Vector2u Labyrinthe::tp(sf::Vector2u tp_tile){ //fonction utile pour greenTile : permet de téléporter le joueur d'une case verte à une autre
    if(tp_tile.y == 5 && tp_tile.x == 7) return sf::Vector2u(8,7);
    else if(tp_tile.y == 7 && tp_tile.x == 7) return sf::Vector2u(4,7);
    else if(tp_tile.y == 19 && tp_tile.x == 17) return sf::Vector2u(19,15);
    else if(tp_tile.y == 20 && tp_tile.x == 15) return sf::Vector2u(20,17);
    else return sf::Vector2u(15,10);
}

void Labyrinthe::Trap(){ //pièges qui enferment le joueur dans une impasse s'il tombe dedans
    if ((player.getCurrentPos().x == 5 && player.getCurrentPos().y == 6) || (player.getCurrentPos().x == 4 && player.getCurrentPos().y == 7) || (player.getCurrentPos().x == 5 && player.getCurrentPos().y == 7)){
        level[7][5] = 16;
        map.load("texture/texture_decor/tileset_lab.png", sf::Vector2u(ftile_size_ingame_lab, ftile_size_ingame_lab), level);
    }
    else if (level[7][5] == 16){
        level[7][5] = 14;
        map.load("texture/texture_decor/tileset_lab.png", sf::Vector2u(ftile_size_ingame_lab, ftile_size_ingame_lab), level);
    }
    if ((player.getCurrentPos().x == 11 && player.getCurrentPos().y == 19)){
        level[19][12] = 1;
        map.load("texture/texture_decor/tileset_lab.png", sf::Vector2u(ftile_size_ingame_lab, ftile_size_ingame_lab), level);
    }
    if ((player.getCurrentPos().x == 5 && player.getCurrentPos().y == 17)){
        level[16][2] = 1;
        map.load("texture/texture_decor/tileset_lab.png", sf::Vector2u(ftile_size_ingame_lab, ftile_size_ingame_lab), level);
    }
    if ((player.getCurrentPos().x == 23 && player.getCurrentPos().y == 15)){
        level[15][24] = 1;
        map.load("texture/texture_decor/tileset_lab.png", sf::Vector2u(ftile_size_ingame_lab, ftile_size_ingame_lab), level);
    }
}

void Labyrinthe::RedTile(){ // case rouge qui téléportle le joueur à la case départ du labyrinthe
    if (level[player.getCurrentPos().y][player.getCurrentPos().x] == 16)
    {
        player.ResetMove();
        player.setPosition(15*32.f, 10*32.f);
        player.setCurrentPos(sf::Vector2u(15,10));
        player.ResetNbPas();
        light_off = false;
    }
}

void Labyrinthe::GreenTile(){ // case verte quie téléporte le joueur vers une autre case verte afin d'avancer dans le labyrinthe
    if (level[player.getCurrentPos().y][player.getCurrentPos().x] == 14){
        player.ResetMove();
        sf::Vector2u new_pos = tp(sf::Vector2u(player.getCurrentPos().y, player.getCurrentPos().x));
        player.setPosition(new_pos.x*32.f, new_pos.y*32.f);
        player.setCurrentPos(new_pos);

    }
}

void Labyrinthe::YellowTile(){ //case jaune qui allume la lumière dans le labyrinthe 
    if (level[player.getCurrentPos().y][player.getCurrentPos().x] == 18){
        player.ResetNbPas();
        light_off = false;
    }
}