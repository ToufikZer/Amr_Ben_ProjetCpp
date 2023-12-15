// MainMenu.cpp
#include "MainMenu.hpp"
#include "iostream"
MainMenu::MainMenu(sf::RenderWindow& window)
    : window(window),
      selectedOption(0) {
        std::cout << "je suis dans mainmenu" << std::endl;
    if (!font.loadFromFile("arial.ttf")) {
        // Gestion de l'erreur lors du chargement de la police
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }

    titleText.setFont(font);
    titleText.setString("My Game Title");
    titleText.setCharacterSize(48);
    titleText.setPosition(window.getSize().x / 2 - titleText.getGlobalBounds().width / 2, 50);

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(32);
    startText.setPosition(window.getSize().x / 2 - startText.getGlobalBounds().width / 2, 200);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(32);
    exitText.setPosition(window.getSize().x / 2 - exitText.getGlobalBounds().width / 2, 300);
}

void MainMenu::handleEvent() {
    // Gestion des événements spécifiques au MainMenu
}

void MainMenu::handleInput() {
    // Gestion des événements spécifiques au MainMenu
}

void MainMenu::update() {
    // Logique de mise à jour spécifique au MainMenu
}

void MainMenu::draw(sf::RenderWindow& window, sf::Font& font) {
    window.clear();

    window.draw(titleText);
    window.draw(startText);
    window.draw(exitText);

    window.display();
}

GameState* MainMenu::getNextState() {
    // Logique pour déterminer le prochain état (peut être nullptr)
    return nullptr;
}

bool MainMenu::isRunning() {
    // Logique pour déterminer si le MainMenu doit continuer à s'exécuter
    return true;
}

// ... autres fonctions membres de la classe MainMenu

