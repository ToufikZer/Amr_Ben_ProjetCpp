#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "InGame.hpp"
#include "iostream"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game State Example");
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.25,sf::VideoMode::getDesktopMode().height * 0.2 ));
    // Initialisation du premier état (MainMenu)
    GameState* currentState = new MainMenu(window);

    sf::Clock clock;
    sf::Time elapsedTime;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return -1;
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Passe l'événement à l'état actuel pour traitement
            currentState->handleEvent(event, window);
        }

        // Mise à jour de l'état actuel
        elapsedTime = clock.restart();
        currentState->update(elapsedTime, window);

        // Dessin de l'état actuel
        currentState->draw(window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            // Libère la mémoire de l'état actuel
            delete currentState;

            // Passe à l'état suivant (InGame)
            currentState = new InGame(window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            // Libère la mémoire de l'état actuel
            delete currentState;

            // Passe à l'état suivant (InGame)
            currentState = new MainMenu(window);
        }
    }

    // Libère la mémoire de l'état final
    delete currentState;

    return 0;
}
