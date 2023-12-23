#include "PseudoInterface.hpp"
#include "iostream"

PseudoInterface::PseudoInterface(sf::RenderWindow& window):
    window(window),
    launch_game(false),
    can_launch(false),
    come_back(false)
    {
        if (!font.loadFromFile("font/Aller_Rg.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        std::exit(-1);
        }
        if (!backgroundTexture.loadFromFile("texture/texture_decor/Titlescreen.jpg")) {
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

        back.setFont(font);
        back.setString("Back");
        ResetBack();

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
            if (back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                come_back = true;
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Return)
        {
            if (can_launch) launch_game = true;
        }
        if (event.key.code == sf::Keyboard::Escape)
        {
            come_back = true;
        }
    }
    else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { //Pour pouvoir effacer
                    if (!pseudo.empty()) {
                        pseudo.pop_back();
                    }
                    // On utilise les caractères ASCII et on retire la touche espace et entrée
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
    }
    else{
        ResetOK();
    }
}

void PseudoInterface::Detect_Back(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (back.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        HighlightBack();
    }
    else{
        ResetBack();
    }
}

void PseudoInterface::update(sf::Time deltaTime, sf::RenderWindow& window){
    float rectangleWidth = window.getSize().x;
    float rectangleHeight = 0.153 * window.getSize().y;
    float rectangleX = 0;
    float rectangleY = 0.3*window.getSize().y;

    if (pseudo.size() > 0) can_launch = true;
    else can_launch = false;

    Detect_OK(window);
    Detect_Back(window);

    pseudo_text.setString("Pseudo : " + pseudo);
    pseudo_text.setPosition(rectangleWidth/2 - pseudo_text.getGlobalBounds().width/2,
                            rectangleY + rectangleHeight /2 - pseudo_text.getGlobalBounds().height/2 - 0.0093*window.getSize().y);
}

void PseudoInterface::draw(sf::RenderWindow& window){
    window.clear();
    window.draw(backgroundSprite);
    window.draw(text);
    window.draw(pseudo_text);
    window.draw(back);
    window.draw(ok);
    window.draw(blueRectangle);
    window.draw(blueRectangleTop);
    window.draw(blueRectangleLeft);
    window.draw(blueRectangleRight);
    window.draw(blueRectangleBot);

    window.display();
}

GameState* PseudoInterface::getNextState() {
    if(launch_game){
        launch_game = false;
        return new InGame(window, sf::Vector2u(0,1), sf::Vector2u(2,3), sf::Vector2u(16,16), 0);
    }
    if(come_back){
        come_back = false;
        return new MainMenu(window);
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
    ok.setFillColor(sf::Color::Green);
}

void PseudoInterface::HighlightBack(){
    back.setCharacterSize(44);
    back.setPosition(window.getSize().x*0.9 - back.getGlobalBounds().width * 0.5, 0.89*window.getSize().y);
    back.setFillColor(sf::Color::Yellow);
}

void PseudoInterface::ResetBack(){
    back.setCharacterSize(36);
    back.setPosition(window.getSize().x*0.9 - back.getGlobalBounds().width * 0.5, 0.9*window.getSize().y);
    back.setFillColor(sf::Color::Red);
}