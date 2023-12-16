#include "Keybinds.hpp"
#include "iostream"

Keybinds::Keybinds(sf::RenderWindow& window):
    window(window)
    {
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
        text.setFont(font);
        text.setString("Press A to interact \n Press R to change the map");
        text.setCharacterSize(44);
        text.setPosition(window.getSize().x*0.46, 0.44*window.getSize().y);
        text.setFillColor(sf::Color::Red);
    }

void Keybinds::handleEvent(sf::Event& event, sf::RenderWindow& window){
    
}
void Keybinds::update(sf::Time deltaTime, sf::RenderWindow& window){

}
void Keybinds::draw(sf::RenderWindow& window){

}