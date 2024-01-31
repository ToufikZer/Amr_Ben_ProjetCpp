#include <SFML/Graphics.hpp>
#include <iostream>

class Enigme {
public:
    std::string question;
    int reponseAttendue;

    Enigme() = default;

    Enigme(const std::string& question, int reponseAttendue, sf::Font font, int id)
        : question(question), reponseAttendue(reponseAttendue), font(font), id(id) {}

    bool verifierReponse() { //retourne true si le joueur donne la bonne réponse, false sinon
        try {
            int reponseUtilisateur = std::stoi(userInput);
            return reponseUtilisateur == reponseAttendue;
        } catch (const std::invalid_argument& e) {
            return false;
        }
    }

    void ajouterCaractere(sf::Uint32 unicode) { //permet au joueur d'écrire quand le jeu le demande
        if (unicode < 128) {
            userInput += static_cast<char>(unicode);
        }
    }

    void supprimerCaractere() { //permet au joueur d'effacer ce qu'il a écrit pour le corriger
        if (!userInput.empty()) {
            userInput.pop_back();
        }
    }

    void reinitialiser() { // vide le userInput
        userInput.clear();
    }

    void setPosition(float x, float y) { //choix de l'emplacement de la boite ou l'énigme sera affichée
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color(169,169,169,236));
        rectangle.setOutlineColor(sf::Color(142, 70, 19));
        rectangle.setOutlineThickness(4);
    }

    void setSize(float width, float height) {
        rectangle.setSize(sf::Vector2f(width, height)); // choix de la taille de la boite
        texteEnigme.setString(question);
        texteEnigme.setCharacterSize(28);
        texteEnigme.setFont(font);
        texteEnigme.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10);
    }

    void afficher(sf::RenderWindow& window) { //affiche la boite
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