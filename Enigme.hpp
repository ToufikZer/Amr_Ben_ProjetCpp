#include <SFML/Graphics.hpp>
#include <iostream>

class Enigme {
public:
    std::string question;
    int reponseAttendue;

    Enigme() = default;

    Enigme(const std::string& question, int reponseAttendue, sf::Font font, int id)
        : question(question), reponseAttendue(reponseAttendue), font(font), id(id) {}

    bool verifierReponse() {
        try {
            int reponseUtilisateur = std::stoi(userInput);
            return reponseUtilisateur == reponseAttendue;
        } catch (const std::invalid_argument& e) {
            return false;
        }
    }

    void ajouterCaractere(sf::Uint32 unicode) {
        if (unicode < 128) {
            userInput += static_cast<char>(unicode);
        }
    }

    void supprimerCaractere() {
        if (!userInput.empty()) {
            userInput.pop_back();
        }
    }

    void reinitialiser() {
        userInput.clear();
    }

    void setPosition(float x, float y) {
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color(169,169,169,236));
        rectangle.setOutlineColor(sf::Color(142, 70, 19));
        rectangle.setOutlineThickness(4);
    }

    void setSize(float width, float height) {
        rectangle.setSize(sf::Vector2f(width, height));
        texteEnigme.setString(question);
        texteEnigme.setCharacterSize(28);
        texteEnigme.setFont(font);
        texteEnigme.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10);
    }

    void afficher(sf::RenderWindow& window) {        
        window.draw(rectangle);

        window.draw(texteEnigme);

        sf::Text userInputText(userInput, font, 20);
        userInputText.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + rectangle.getSize().y - 30);
        window.draw(userInputText);
    }

    int getId(){
        return id;
    }

private:
    std::string userInput;
    sf::Texture texture;
    sf::RectangleShape rectangle;
    sf::Font font;
    sf::Text texteEnigme;
    int id;
};