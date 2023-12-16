// MainMenu.cpp
#include "MainMenu.hpp"
#include "InGame.hpp"
#include "iostream"

MainMenu::MainMenu(sf::RenderWindow& window)
    : window(window),
      selectedOption(0),
      start_game(false) {
        // std::cout << "je suis dans mainmenu" << std::endl;
    if (!font.loadFromFile("font/Aller_Rg.ttf")) {
        // Gestion de l'erreur lors du chargement de la police
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }
    if (!backgroundTexture.loadFromFile("texture/texture_decor/Titlescreen.jpg")) {
        // Gestion de l'erreur si le chargement échoue
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
}
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0,0);
    titleText.setFont(font);
    titleText.setString("My Game Title");
    titleText.setCharacterSize(64);
    titleText.setPosition(window.getSize().x / 2 - titleText.getGlobalBounds().width / 2 + 20.f, 50);
    titleText.setFillColor(sf::Color(50,50,200,250));

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(44);
    startText.setPosition(window.getSize().x*0.4, 0.44*window.getSize().y);
    startText.setFillColor(sf::Color(50,200,50,250));

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(44);
    exitText.setPosition(window.getSize().x*0.4, 0.55*window.getSize().y);
    exitText.setFillColor(sf::Color(200,50,50,250));

}

void MainMenu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (startText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                std::cout << "start the game" << std::endl;
                start_game = true;
            }
            if (exitText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                window.close();
            }
        }
    }
    // if (event.type == sf::Event::Resized)
    // {
    //     window.getSize().x = event.size.width;
    //     window.getSize().y = event.size.height;
    // }
}

void MainMenu::Detect_Start(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (startText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        startText.setCharacterSize(50);
        startText.setFillColor(sf::Color(200,200,50,250));
        startText.setPosition(window.getSize().x*0.4, 0.43*window.getSize().y);
        //std::cout << startText.getGlobalBounds().width << std::endl;
    }
    else{
        startText.setCharacterSize(44);
        startText.setPosition(window.getSize().x*0.4, 0.44*window.getSize().y);
        startText.setFillColor(sf::Color(50,200,50,250));
    }
}

void MainMenu::Detect_Exit(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (exitText.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        exitText.setCharacterSize(50);
        exitText.setFillColor(sf::Color(200,200,50,250));
        exitText.setPosition(window.getSize().x*0.4, 0.54*window.getSize().y);
    }
    else{
        exitText.setCharacterSize(44);
        exitText.setPosition(window.getSize().x*0.4, 0.55*window.getSize().y);
        exitText.setFillColor(sf::Color(200,50,50,250));
    }
}

void MainMenu::update(sf::Time deltaTime, sf::RenderWindow& window) {
    Detect_Start(window);
    Detect_Exit(window);
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(startText);
    window.draw(exitText);

    window.display();
}

GameState* MainMenu::getNextState() {
    // Logique pour déterminer le prochain état (peut être nullptr)
    if(start_game){
        start_game = false;
        return new InGame(window);
    }
    return nullptr;
}

bool MainMenu::isRunning() {
    // Logique pour déterminer si le MainMenu doit continuer à s'exécuter
    return true;
}

// ... autres fonctions membres de la classe MainMenu

