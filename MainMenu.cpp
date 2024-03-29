// MainMenu.cpp
#include "MainMenu.hpp"
#include "iostream"

MainMenu::MainMenu(sf::RenderWindow& window, Save save)
    : window(window),
      selectedOption(0),
      start_game(false),
      continue_game(false),
      keyboard_pressed(false),
      save(save) 
      {
    if (!font.loadFromFile("font/Aller_Rg.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }
    if (!backgroundTexture.loadFromFile("texture/texture_decor/Titlescreen.jpg")) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
}
    view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0,0);
    
    initialize_text();

    window.setKeyRepeatEnabled(false);
}

void MainMenu::initialize_text(){ //initialisation du menu principal
    titleText.setFont(font);
    titleText.setString("J.O Tourismo");
    titleText.setCharacterSize(64);
    titleText.setPosition(view.getSize().x / 2 - titleText.getGlobalBounds().width / 2 + 20.f, 50);
    titleText.setFillColor(sf::Color(50,50,200,250));

    continueText.setFont(font);
    continueText.setString("Continuer");
    ResetContinue();

    startText.setFont(font);
    startText.setString("Nouvelle Partie");
    ResetStart();

    exitText.setFont(font);
    exitText.setString("Quitter");
    ResetExit();
}

void MainMenu::handleEvent(sf::Event& event, sf::RenderWindow& window) { //inputs joueur
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (continueText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y) && save.getGameStarted())
            {
                continue_game = true;
            }
            if (startText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                start_game = true;
            }
            if (exitText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                window.close();
            }
        }
    }

    if (event.type == sf::Event::KeyPressed)
    {
        keyboard_pressed = true;
        if (event.key.code == sf::Keyboard::Return)
        {
            executeOption();
        }
        if (event.key.code == sf::Keyboard::Up)
        {
            moveUp();
        }
        if (event.key.code == sf::Keyboard::Down)
        {
            moveDown();
        }
    }
}

void MainMenu::Detect_Continue(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (continueText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        keyboard_pressed = false;
        selectedOption = -1;
        HighlightContinue();
    }
    else{
        if (!keyboard_pressed)
        {
        selectedOption = 0;
        ResetContinue();
        }
    }
}

void MainMenu::Detect_Start(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (startText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        keyboard_pressed = false;
        selectedOption = 3;
        HighlightStart();
    }
    else{
        if (!keyboard_pressed)
        {
        selectedOption = 0;
        ResetStart();
        }
    }
}

void MainMenu::Detect_Exit(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (exitText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {   
        selectedOption = 1;
        keyboard_pressed = false;
        HighlightExit();
    }
    else{
        if (!keyboard_pressed)
        {
        selectedOption = 0;
        ResetExit();
        }
    }
}


void MainMenu::update(sf::Time deltaTime, sf::RenderWindow& window) { //traitement à chaque frame pour le jeu
    // On permet a l'utilisateur de detecter au clavier et a la souris en meme temps prcq sinon ca reset keyboard_pressed
        if (selectedOption != 3) Detect_Start(window);
        if (selectedOption != 1) Detect_Exit(window);
        if (selectedOption != -1 && save.getGameStarted()) Detect_Continue(window);
        }

void MainMenu::draw(sf::RenderWindow& window, sf::Event& event) { //affichage sur l'écran du joueur
    window.clear();
    window.setView(view);
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(continueText);
    window.draw(startText);
    window.draw(exitText);
    window.display();
}

GameState* MainMenu::getNextState() { // indique les différents cas de figure à la fin de l'état MainMenu
    if(start_game){
        start_game = false;
        return new PseudoInterface(window, save);
    }
    else if(continue_game){
        continue_game = false;
        if (save.getStateName() == "InGame") return new InGame(window, save.getCurrentMap(), save.getPlayerPosition(), save.getmapDimension(), save.getInventory(), 3, "Easter egg : Cherchez bien vous\npourrez trouver des objets utiles", save.getCombatWin());
        if (save.getStateName() == "InDoors") return new Indoors(window, save.getName(), save.getPlayerPosition().x, save.getPlayerPosition().y, save.getInventory(), "Easter Egg : On travaille \nsur une V2", save.getCombatWin());
        if (save.getStateName() == "Labyrinthe") return new Labyrinthe(window, save.getNbPas(), sf::Vector2f(save.getPlayerPosition().x, save.getPlayerPosition().y), save.getmapDimension(), save.getInventory(), 3);
    }
    return nullptr;
}

// consequence du clavier si on presse Up
void MainMenu::moveUp(){
    switch(selectedOption)
    {
    case 0:
    HighlightStart();
    selectedOption = 3;
    break;
    case 1:
    HighlightStart();
    ResetExit();
    selectedOption = 3;
    break;
    case 3:
    if (save.getGameStarted()) {
        HighlightContinue();
        ResetStart();
        selectedOption = -1;
        break;
        }
    }

// consequence du clavier si on presse Down
}
void MainMenu::moveDown(){
    switch(selectedOption)
    {
    case 0:
    HighlightStart();
    selectedOption = 3;
    break;
    case 3:
    HighlightExit();
    ResetStart();
    selectedOption = 1;
    break;
    case -1:
    if (save.getGameStarted()) {
        HighlightStart();
        ResetContinue();
        selectedOption = 3;
        break;
        }
    }
}

// consequence du clavier si on presse Enter
void MainMenu::executeOption(){
    if (selectedOption == -1) continue_game = true;
    if (selectedOption == 3) start_game = true;
    if (selectedOption == 1) window.close();
}

void MainMenu::HighlightContinue(){
    continueText.setCharacterSize(50);
    continueText.setFillColor(sf::Color(200,200,50,250));
    continueText.setPosition(view.getSize().x*0.43, 0.32*view.getSize().y);
}

void MainMenu::ResetContinue(){
    continueText.setCharacterSize(44);
    continueText.setPosition(view.getSize().x*0.43, 0.33*view.getSize().y);
    if (save.getGameStarted()) continueText.setFillColor(sf::Color(220,220,220,250));
    else continueText.setFillColor(sf::Color(100,100,100,150));
}

void MainMenu::HighlightStart(){
    startText.setCharacterSize(50);
    startText.setFillColor(sf::Color(200,200,50,250));
    startText.setPosition(view.getSize().x*0.43, 0.43*view.getSize().y);
}

void MainMenu::ResetStart(){
    startText.setCharacterSize(44);
    startText.setPosition(view.getSize().x*0.43, 0.44*view.getSize().y);
    startText.setFillColor(sf::Color(50,200,50,250));
}

void MainMenu::HighlightExit(){
    exitText.setCharacterSize(50);
    exitText.setFillColor(sf::Color(200,200,50,250));
    exitText.setPosition(view.getSize().x*0.43, 0.65*view.getSize().y);
}

void MainMenu::ResetExit(){
    exitText.setCharacterSize(44);
    exitText.setPosition(view.getSize().x*0.43, 0.66*view.getSize().y);
    exitText.setFillColor(sf::Color(200,50,50,250));
}