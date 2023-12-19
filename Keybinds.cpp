#include "Keybinds.hpp"
#include "iostream"

Keybinds::Keybinds(sf::RenderWindow& window):
    window(window),
    come_back(false)
    {
        if (!font.loadFromFile("font/Aller_Rg.ttf")) {
        // Gestion de l'erreur lors du chargement de la police
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
        }
        if (!backgroundTexture.loadFromFile("texture/texture_decor/keybinds.png")) {
        // Gestion de l'erreur si le chargement échoue
        std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
        std::exit(-1);
        }

        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setPosition(0,0);

        text.setFont(font);
        text.setString("Press A to interact \nLeft : Q or Left button\nRight : D or Right button\nUp : Z or Up button\nDown : S or Down button\n\n\nEscape to return to the Title Screen");
        text.setCharacterSize(44);
        text.setPosition(window.getSize().x*0.5 - text.getGlobalBounds().width * 0.5, 0.08*window.getSize().y);
        text.setFillColor(sf::Color::Red);

        back.setFont(font);
        back.setString("Back");
        ResetBack();

    }

void Keybinds::handleEvent(sf::Event& event, sf::RenderWindow& window){
if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                come_back = true;
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            come_back = true;
        }
    }
}

void Keybinds::Detect_Back(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (back.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        HighlightBack();
        //std::cout << startText.getGlobalBounds().width << std::endl;
    }
    else{
        ResetBack();
    }
}

void Keybinds::update(sf::Time deltaTime, sf::RenderWindow& window){
    Detect_Back(window);
}
void Keybinds::draw(sf::RenderWindow& window){
    window.clear();
    window.draw(backgroundSprite);
    window.draw(text);
    window.draw(back);
    window.display();
}

GameState* Keybinds::getNextState() {
    // Logique pour déterminer le prochain état (peut être nullptr)
    if(come_back){
        come_back = false;
        return new MainMenu(window);
    }
    return nullptr;
}

void Keybinds::HighlightBack(){
    back.setCharacterSize(44);
    back.setPosition(window.getSize().x*0.9 - back.getGlobalBounds().width * 0.5, 0.89*window.getSize().y);
    back.setFillColor(sf::Color::Yellow);
}

void Keybinds::ResetBack(){
    back.setCharacterSize(36);
    back.setPosition(window.getSize().x*0.9 - back.getGlobalBounds().width * 0.5, 0.9*window.getSize().y);
    back.setFillColor(sf::Color::Red);
}