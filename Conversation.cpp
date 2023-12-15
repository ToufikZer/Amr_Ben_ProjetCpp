// Conversation.cpp
#include "Conversation.hpp"
#include "iostream"

Conversation::Conversation(sf::RenderWindow& window)
    : window(window),
      current_message(0)
      {
        if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
    }
        message.setFont(font);
        message.setFillColor(sf::Color::Black);
      }

    void Conversation::update(sf::Time deltaTime,sf::RenderWindow& window){
        Rectangle(sf::Vector2f(window.getSize().x, 0.847* window.getSize().y));
        RectangleTop(sf::Vector2f(window.getSize().x, 0.0093*window.getSize().y));
        RectangleLeft(sf::Vector2f(0.0093*window.getSize().y, 0.153* window.getSize().y));
        RectangleRight(sf::Vector2f(0.0093*window.getSize().y, 0.153* window.getSize().y));
        RectangleBot(sf::Vector2f(window.getSize().x, 0.0093*window.getSize().y));
        message.setString(dialogue[current_message]);
        message.setCharacterSize(0.1 * window.getSize().x);
        Rectangle.setPosition(0.f, 0.847* window.getSize().y);
        Rectangle.setFillColor(sf::Color(200, 200, 200, 100));
        RectangleTop.setPosition(0.f, 0.847* window.getSize().y);
        RectangleTop.setFillColor(sf::Color(50, 50, 50, 200));
        RectangleLeft.setPosition(0.f, 0.847* window.getSize().y);
        RectangleLeft.setFillColor(sf::Color(50, 50, 50, 200));
        RectangleRight.setPosition(window.getSize().x - 0.0093*window.getSize().y, 0.847* window.getSize().y);
        RectangleRight.setFillColor(sf::Color(50, 50, 50, 200));
        RectangleBot.setPosition(0.f, window.getSize().y - 0.0093*ViewRect.height);
        RectangleBot.setFillColor(sf::Color(50, 50, 50, 200));
        message.setPosition(0.f + 0.0156 * window.getSize().x, 0.847* window.getSize().y + 0.0088* window.getSize().x);
    }

    void Conversation::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(Rectangle);
    window.draw(RectangleTop);
    window.draw(RectangleLeft);
    window.draw(RectangleRight);
    window.draw(RectangleBot);
    window.draw(message);
    window.display();
}

void Conversation::handleEvent(sf::Event& event, sf::RenderWindow& window) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A) {
                for (NPC& npc : NPCs) {
                    if (!isTalking && player.is_looking_at(npc)) {
                        isTalking = true;
                        npc.setIsTalking(true);
                        npc.update(player, sf::Time::Zero, map, nullptr);
                        npcThatWasTalking = &npc;
                        break;
                    } else if ((&npc == npcThatWasTalking) && isTalking && (currentMessage < npc.getDialogue().size() - 1)) {
                        currentMessage += 1;
                        break;
                    } else {
                        if (npcThatWasTalking != nullptr) {
                            if (&npc == npcThatWasTalking) {
                                isTalking = false;
                                currentMessage = 0;
                                npcThatWasTalking->setIsTalking(false);
                            }
                        }
                    }
                }
            } else if (event.key.code == sf::Keyboard::P) {
                window.setSize(sf::Vector2u(800, 600));
                initialize(); // Réinitialiser l'état après le changement de taille
            }
        }
    }