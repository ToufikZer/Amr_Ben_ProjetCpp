#include "PseudoInterface.hpp"
#include "iostream"

PseudoInterface::PseudoInterface(sf::RenderWindow& window):
    window(window),
    launch_game(false),
    can_launch(false)
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

        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setPosition(0,0);

        text.setFont(font);
        text.setString("Enter your nickname");
        text.setCharacterSize(44);
        text.setPosition(window.getSize().x*0.5 - text.getGlobalBounds().width * 0.5, 0.1*window.getSize().y);
        text.setFillColor(sf::Color::Red);

        ok.setFont(font);
        ok.setString("OK");
        ResetOK();

        float rectangleWidth = window.getSize().x;
        float rectangleHeight = 0.153 * window.getSize().y;
        float rectangleX = 0;
        float rectangleY = 0.3*window.getSize().y;

        blueRectangle.setSize(sf::Vector2f(rectangleWidth, 0.153 * window.getSize().y));
        blueRectangleTop.setSize(sf::Vector2f(rectangleWidth, 0.0093*window.getSize().y));
        blueRectangleLeft.setSize(sf::Vector2f(0.0093*window.getSize().y, 0.153 * window.getSize().y));
        blueRectangleRight.setSize(sf::Vector2f(0.0093*window.getSize().x, 0.153 * window.getSize().y));
        blueRectangleBot.setSize(sf::Vector2f(rectangleWidth, 0.0093*window.getSize().y));
        blueRectangle.setPosition(rectangleX, rectangleY);
        blueRectangle.setFillColor(sf::Color(200, 200, 200, 100));
        blueRectangleTop.setPosition(rectangleX, rectangleY);
        blueRectangleTop.setFillColor(sf::Color(50, 50, 50, 200));
        blueRectangleLeft.setPosition(rectangleX, rectangleY);
        blueRectangleLeft.setFillColor(sf::Color(50, 50, 50, 200));
        blueRectangleRight.setPosition(rectangleWidth - 0.0093*window.getSize().y, rectangleY);
        blueRectangleRight.setFillColor(sf::Color(50, 50, 50, 200));
        blueRectangleBot.setPosition(rectangleX, 0.453*window.getSize().y);
        blueRectangleBot.setFillColor(sf::Color(50, 50, 50, 200));

        pseudo_text.setFont(font);
        pseudo_text.setPosition(rectangleWidth/2 - pseudo_text.getGlobalBounds().width/2, 
                                rectangleY  + rectangleHeight /2 - pseudo_text.getGlobalBounds().height/2 - 0.0093*window.getSize().y);
        pseudo_text.setCharacterSize(36);
        pseudo_text.setFillColor(sf::Color::White);
    }

void PseudoInterface::handleEvent(sf::Event& event, sf::RenderWindow& window){
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (ok.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                if (can_launch) launch_game = true;
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Return)
        {
            if (can_launch) launch_game = true;
        }
    }
    else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { //Pour pouvoir effacer
                    if (!pseudo.empty()) {
                        pseudo.pop_back();
                    }
                    // On utilise les caractères ASCII et on retire la touche espace et entrer
                } else if (event.text.unicode < 128 && event.text.unicode != ' ' && event.text.unicode != 13) { 
                    pseudo += static_cast<char>(event.text.unicode);
                }
            }
}

void PseudoInterface::Detect_OK(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (ok.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        HighlightOK();
        //std::cout << startText.getGlobalBounds().width << std::endl;
    }
    else{
        ResetOK();
    }
}

void PseudoInterface::update(sf::Time deltaTime, sf::RenderWindow& window){
    // essayer darranger ca
    float rectangleWidth = window.getSize().x;
    float rectangleHeight = 0.153 * window.getSize().y;
    float rectangleX = 0;
    float rectangleY = 0.3*window.getSize().y;

    if (pseudo.size() > 0) can_launch = true;
    else can_launch = false;

    Detect_OK(window);
    pseudo_text.setString("Pseudo : " + pseudo);
    pseudo_text.setPosition(rectangleWidth/2 - pseudo_text.getGlobalBounds().width/2,
                            rectangleY + rectangleHeight /2 - pseudo_text.getGlobalBounds().height/2 - 0.0093*window.getSize().y);
}
void PseudoInterface::draw(sf::RenderWindow& window){
    window.clear();
    window.draw(backgroundSprite);
    window.draw(text);
    window.draw(pseudo_text);
    window.draw(ok);
    window.draw(blueRectangle);
    window.draw(blueRectangleTop);
    window.draw(blueRectangleLeft);
    window.draw(blueRectangleRight);
    window.draw(blueRectangleBot);

    window.display();
}

GameState* PseudoInterface::getNextState() {
    // Logique pour déterminer le prochain état (peut être nullptr)
    if(launch_game){
        launch_game = false;
        return new InGame(window);
    }
    return nullptr;
}

void PseudoInterface::HighlightOK(){
    ok.setCharacterSize(44);
    ok.setPosition(window.getSize().x*0.9 - ok.getGlobalBounds().width * 0.5, 0.49*window.getSize().y);
    ok.setFillColor(sf::Color::Yellow);
}

void PseudoInterface::ResetOK(){
    ok.setCharacterSize(36);
    ok.setPosition(window.getSize().x*0.9 - ok.getGlobalBounds().width * 0.5, 0.5*window.getSize().y);
    ok.setFillColor(sf::Color::Red);
}