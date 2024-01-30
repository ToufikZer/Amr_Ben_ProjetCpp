#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

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
            // Gérer l'erreur si la conversion échoue
            return false;
        }
    }

    void ajouterCaractere(sf::Uint32 unicode) {
        if (unicode < 128) {
            // Seuls les caractères ASCII sont autorisés
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

        // Ajuster la position du texte dans le rectangle
        texteEnigme.setString(question);
        texteEnigme.setCharacterSize(28);
        texteEnigme.setFont(font);
        texteEnigme.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10);
    }

    void afficher(sf::RenderWindow& window) {
        // Afficher le rectangle en fond
        
        window.draw(rectangle);

        // Afficher le texte de l'énigme
        window.draw(texteEnigme);

        // Afficher la zone de saisie
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