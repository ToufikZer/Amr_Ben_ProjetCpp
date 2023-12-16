#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "InGame.hpp"
#include "iostream"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "JO Tourismo");
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.25,sf::VideoMode::getDesktopMode().height * 0.20 ));
    // Initialisation du premier état (MainMenu)
    GameState* currentState = new MainMenu(window);

    sf::Clock clock;
    sf::Time elapsedTime;

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            // Libère la mémoire de l'état actuel
            delete currentState;

            // Passe à l'état suivant (InGame)
            currentState = new MainMenu(window);
        }
        
        GameState* nextState = currentState->getNextState();
        if (nextState != nullptr) {
            // Libérez l'ancien état (dans un projet réel, utilisez std::unique_ptr)
            delete currentState;
            currentState = nextState;
        }
    }

    // Libère la mémoire de l'état final
    delete currentState;

    return 0;
}
