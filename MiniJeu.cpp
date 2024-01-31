// MiniJeu.cpp
#include "MiniJeu.hpp"
#include "iostream"

MiniJeu::MiniJeu(sf::RenderWindow& window, Save save)
    : window(window),
      selectedOption(0),
      bagarre_game(false),
      car_game(false),
      fraude_game(false),
      keyboard_pressed(false),
      save(save) {
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

void MiniJeu::initialize_text(){
    titleText.setFont(font);
    titleText.setString("Mini-Jeux");
    titleText.setCharacterSize(64);
    titleText.setPosition(view.getSize().x / 2 - titleText.getGlobalBounds().width / 2 + 20.f, 50);
    titleText.setFillColor(sf::Color(50,50,200,250));

    bagarreText.setFont(font);
    bagarreText.setString("Jeu de Bagarre");
    ResetBagarre();

    carText.setFont(font);
    carText.setString("Jeu de course");
    ResetCar();

    fraudeText.setFont(font);
    fraudeText.setString("Jeu de la fraude");
    ResetFraude();

    exitText.setFont(font);
    exitText.setString("Quitter");
    ResetExit();
}

void MiniJeu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (bagarreText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                bagarre_game = true;
            }
            if (carText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                car_game = true;
            }
            if (exitText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                window.close();
            }
            if (fraudeText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                fraude_game = true;
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

void MiniJeu::Detect_Bagarre(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (bagarreText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        keyboard_pressed = false;
        selectedOption = -1;
        HighlightBagarre();
    }
    else{
        if (!keyboard_pressed)
        {
        selectedOption = 0;
        ResetBagarre();
        }
    }
}

void MiniJeu::Detect_Car(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (carText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        keyboard_pressed = false;
        selectedOption = 3;
        HighlightCar();
    }
    else{
        if (!keyboard_pressed)
        {
        selectedOption = 0;
        ResetCar();
        }
    }
}

void MiniJeu::Detect_Fraude(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (fraudeText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        keyboard_pressed = false;
        selectedOption = 2;
        HighlightFraude();
    }
    else{
        if (!keyboard_pressed)
        {
        selectedOption = 0;
        ResetFraude();
        }
    }
}

void MiniJeu::Detect_Exit(sf::RenderWindow& window){
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


void MiniJeu::update(sf::Time deltaTime, sf::RenderWindow& window) {
    // On permet a l'utilisateur de detecter au clavier et a la souris en meme temps prcq sinon ca reset keyboard_pressed
        if (selectedOption != 3) Detect_Car(window);
        if (selectedOption != 2) Detect_Fraude(window);
        if (selectedOption != 1) Detect_Exit(window);
        if (selectedOption != -1) Detect_Bagarre(window);
        }

void MiniJeu::draw(sf::RenderWindow& window, sf::Event& event) {
    window.clear();
    window.setView(view);
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(bagarreText);
    window.draw(carText);
    window.draw(exitText);
    window.draw(fraudeText);
    window.display();
}

GameState* MiniJeu::getNextState() {
    if(car_game){
        car_game = false;
        return new InGame_CarGameplay(window, save, save.getInventory(), true);
    }
    else if(fraude_game){
        fraude_game = false;
        return new FraudeGameplay(window, save, save.getInventory(), true);
    }
    else if(bagarre_game){
        bagarre_game = false;
        return new Bagarre(window, save, save.getInventory(), "texture/texture_decor/2Qpng.png", "texture/texture_char/etudiant.png", 8, 40, 500, 800, 1, true);
    }
    return nullptr;
}

bool MiniJeu::isRunning() {
    return true;
}

// consequence du clavier si on presse Up
void MiniJeu::moveUp(){
    switch(selectedOption)
    {
    case 0:
    HighlightCar();
    selectedOption = 3;
    break;
    case 1:
    HighlightFraude();
    ResetExit();
    selectedOption = 2;
    break;
    case 2:
    HighlightCar();
    ResetFraude();
    selectedOption = 3;
    break;
    case 3:
    HighlightBagarre();
    ResetCar();
    selectedOption = -1;
    break;
    }
    // consequence du clavier si on presse Down
}
void MiniJeu::moveDown(){
    switch(selectedOption)
    {
    case 0:
    HighlightCar();
    selectedOption = 3;
    break;
    case 3:
    HighlightFraude();
    ResetCar();
    selectedOption = 2;
    break;
    case 2:
    HighlightExit();
    ResetFraude();
    selectedOption = 1;
    break;
    case -1:
    HighlightCar();
    ResetBagarre();
    selectedOption = 3;
    break;
    }
}

// consequence du clavier si on presse Enter

void MiniJeu::executeOption(){
    if (selectedOption == -1) bagarre_game = true;
    if (selectedOption == 3) car_game = true;
    if (selectedOption == 2) fraude_game = true;
    if (selectedOption == 1) window.close();
}

void MiniJeu::HighlightBagarre(){
    bagarreText.setCharacterSize(50);
    bagarreText.setFillColor(sf::Color(200,200,50,250));
    bagarreText.setPosition(view.getSize().x*0.43, 0.32*view.getSize().y);
}

void MiniJeu::ResetBagarre(){
    bagarreText.setCharacterSize(44);
    bagarreText.setPosition(view.getSize().x*0.43, 0.33*view.getSize().y);
    bagarreText.setFillColor(sf::Color(220,220,220,250));
}

void MiniJeu::HighlightCar(){
    carText.setCharacterSize(50);
    carText.setFillColor(sf::Color(200,200,50,250));
    carText.setPosition(view.getSize().x*0.43, 0.43*view.getSize().y);
}

void MiniJeu::ResetCar(){
    carText.setCharacterSize(44);
    carText.setPosition(view.getSize().x*0.43, 0.44*view.getSize().y);
    carText.setFillColor(sf::Color(50,200,50,250));
}

void MiniJeu::HighlightFraude(){
    fraudeText.setCharacterSize(50);
    fraudeText.setFillColor(sf::Color(200,200,50,250));
    fraudeText.setPosition(view.getSize().x*0.43, 0.54*view.getSize().y);
}

void MiniJeu::ResetFraude(){
    fraudeText.setCharacterSize(44);
    fraudeText.setPosition(view.getSize().x*0.43, 0.55*view.getSize().y);
    fraudeText.setFillColor(sf::Color(200,150,150,250));
}

void MiniJeu::HighlightExit(){
    exitText.setCharacterSize(50);
    exitText.setFillColor(sf::Color(200,200,50,250));
    exitText.setPosition(view.getSize().x*0.43, 0.65*view.getSize().y);
}

void MiniJeu::ResetExit(){
    exitText.setCharacterSize(44);
    exitText.setPosition(view.getSize().x*0.43, 0.66*view.getSize().y);
    exitText.setFillColor(sf::Color(200,50,50,250));
}