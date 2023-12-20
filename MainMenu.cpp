// MainMenu.cpp
#include "MainMenu.hpp"
#include "InGame.hpp"
#include "Keybinds.hpp"
#include "PseudoInterface.hpp"
#include "iostream"

MainMenu::MainMenu(sf::RenderWindow& window)
    : window(window),
      selectedOption(0),
      start_game(false),
      keybinds(false),
      keyboard_pressed(false) {
        //std::cout << "je suis dans mainmenu" << std::endl;
    if (!font.loadFromFile("font/Aller_Rg.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }
    if (!backgroundTexture.loadFromFile("texture/texture_decor/Titlescreen.jpg")) {
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
}
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0,0);
    
    titleText.setFont(font);
    titleText.setString("J.O Tourismo");
    titleText.setCharacterSize(64);
    titleText.setPosition(window.getSize().x / 2 - titleText.getGlobalBounds().width / 2 + 20.f, 50);
    titleText.setFillColor(sf::Color(50,50,200,250));

    startText.setFont(font);
    startText.setString("Start Game");
    ResetStart();

    ctrlText.setFont(font);
    ctrlText.setString("How to Play");
    ResetCtrl();

    exitText.setFont(font);
    exitText.setString("Exit");
    ResetExit();

    window.setKeyRepeatEnabled(false);
}

void MainMenu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (startText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                start_game = true;
            }
            if (exitText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                window.close();
            }
            if (ctrlText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                keybinds = true;
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

void MainMenu::Detect_Start(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (startText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        keyboard_pressed = false;
        selectedOption = 3;
        HighlightStart();
        //std::cout << startText.getGlobalBounds().width << std::endl;
    }
    else{
        if (!keyboard_pressed)
        {
        selectedOption = 0;
        ResetStart();
        }
    }
}

void MainMenu::Detect_Ctrl(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (ctrlText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        keyboard_pressed = false;
        selectedOption = 2;
        HighlightCtrl();
        //std::cout << startText.getGlobalBounds().width << std::endl;
    }
    else{
        if (!keyboard_pressed)
        {
        selectedOption = 0;
        ResetCtrl();
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


void MainMenu::update(sf::Time deltaTime, sf::RenderWindow& window) {
    // On permet a l'utilisateur de detecter au clavier et a la souris en meme temps prcq sinon ca reset keyboard_pressed
        if (selectedOption != 3) Detect_Start(window);
        if (selectedOption != 2) Detect_Ctrl(window);
        if (selectedOption != 1) Detect_Exit(window);
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(startText);
    window.draw(exitText);
    window.draw(ctrlText);
    window.display();
}

GameState* MainMenu::getNextState() {
    // Logique pour déterminer le prochain état (peut être nullptr)
    if(start_game){
        start_game = false;
        return new PseudoInterface(window);
    }
    else if (keybinds) {
        keybinds = false;
        return new Keybinds(window);
    }
    return nullptr;
}

bool MainMenu::isRunning() {
    // Logique pour déterminer si le MainMenu doit continuer à s'exécuter
    return true;
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
    HighlightCtrl();
    ResetExit();
    selectedOption = 2;
    break;
    case 2:
    HighlightStart();
    ResetCtrl();
    selectedOption = 3;
    break;
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
    HighlightCtrl();
    ResetStart();
    selectedOption = 2;
    break;
    case 2:
    HighlightExit();
    ResetCtrl();
    selectedOption = 1;
    break;
    }
}

// consequence du clavier si on presse Enter

void MainMenu::executeOption(){
    if (selectedOption == 3) start_game = true;
    if (selectedOption == 2) keybinds = true;
    if (selectedOption == 1) window.close();
}

void MainMenu::HighlightStart(){
    startText.setCharacterSize(50);
    startText.setFillColor(sf::Color(200,200,50,250));
    startText.setPosition(window.getSize().x*0.43, 0.43*window.getSize().y);
}

void MainMenu::ResetStart(){
    startText.setCharacterSize(44);
    startText.setPosition(window.getSize().x*0.43, 0.44*window.getSize().y);
    startText.setFillColor(sf::Color(50,200,50,250));
}

void MainMenu::HighlightCtrl(){
    ctrlText.setCharacterSize(50);
    ctrlText.setFillColor(sf::Color(200,200,50,250));
    ctrlText.setPosition(window.getSize().x*0.43, 0.54*window.getSize().y);
}

void MainMenu::ResetCtrl(){
    ctrlText.setCharacterSize(44);
    ctrlText.setPosition(window.getSize().x*0.43, 0.55*window.getSize().y);
    ctrlText.setFillColor(sf::Color(200,150,150,250));
}

void MainMenu::HighlightExit(){
    exitText.setCharacterSize(50);
    exitText.setFillColor(sf::Color(200,200,50,250));
    exitText.setPosition(window.getSize().x*0.43, 0.65*window.getSize().y);
}

void MainMenu::ResetExit(){
    exitText.setCharacterSize(44);
    exitText.setPosition(window.getSize().x*0.43, 0.66*window.getSize().y);
    exitText.setFillColor(sf::Color(200,50,50,250));
}