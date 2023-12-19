#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "InGame.hpp"
#include "iostream"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
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

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        //     // Libère la mémoire de l'état actuel
        //     delete currentState;

        //     // Passe à l'état suivant (InGame)
        //     currentState = new MainMenu(window);
        // }
        
        GameState* nextState = currentState->getNextState();
        if (nextState != nullptr) {
            // Libérez l'ancien état (dans un projet réel, utilisez std::unique_ptr)
            delete currentState;
            currentState = nextState;
            sf::RectangleShape blackoutScreen(sf::Vector2f(window.getSize().x, window.getSize().y));
            blackoutScreen.setFillColor(sf::Color::Black);

            // on affiche l'écran noir progressivement pour transition
            for (int alpha = 0; alpha <= 25; alpha += 1) {
                blackoutScreen.setFillColor(sf::Color(150, 150, 150, alpha));
                //window.clear();
                window.draw(blackoutScreen);
                window.display();
                
                sf::sleep(sf::milliseconds(10));
            }
        }
    }

    // Libère la mémoire de l'état final
    delete currentState;

    return 0;
}
