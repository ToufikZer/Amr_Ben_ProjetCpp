#include "NPC.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

    NPC::NPC(const std::string& texturePath, unsigned int pos_x,unsigned int pos_y, std::vector<std::string> dialogue): Player(texturePath, pos_x, pos_y), current_pos(pos_x,pos_y), dialogue(dialogue) {
        // Charger la texture du joueur
        if (!m_texture.loadFromFile(texturePath)) {
            // Gestion de l'erreur si le chargement échoue
            // ...
        }

        // Initialisation du tableau de sommets (quad pour le joueur)
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(4);

        // Définir la géométrie du joueur
        m_vertices[0].position = sf::Vector2f(0.f, 0.f);
        m_vertices[1].position = sf::Vector2f(m_texture.getSize().x /3, 0.f);
        m_vertices[2].position = sf::Vector2f(m_texture.getSize().x/3, m_texture.getSize().y/4);
        m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y/4);

        // Définir les coordonnées de texture pour chaque sommet
        m_vertices[0].texCoords = sf::Vector2f(0.f, 32.f);
        m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x/3, 32.f);
        m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x/3, 32.f + m_texture.getSize().y/4);
        m_vertices[3].texCoords = sf::Vector2f(0.f, 32.F + m_texture.getSize().y/4);

        // Appliquer la texture au tableau de sommets
        m_vertices[0].color = sf::Color::White;
        m_vertices[1].color = sf::Color::White;
        m_vertices[2].color = sf::Color::White;
        m_vertices[3].color = sf::Color::White;

        setPosition(pos_x*32.f,pos_y*32.f);
    }

    sf::Vector2u NPC::getCurrentPos(){
    return current_pos;
}
    // Implémentez la fonction draw pour dessiner le joueur
    void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform(); // Appliquer la transformation
        states.texture = &m_texture; // Appliquer la texture

        // Dessiner le joueur en utilisant le tableau de sommets
        target.draw(m_vertices, states);
    }

    // Mettez à jour la position du joueur en fonction des entrées utilisateur
    void NPC::update(Player& player,const sf::Time& deltaTime, const TileMap& map, const int* plan) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        //std::cout << is_talking << std::endl;        
        if (is_talking){
        // std::cout << "is_talking" << std::endl;
            if (player.getDirection() == "R") update_texture(0,2, sf::Vector2f(32,32));
            if (player.getDirection() == "L") update_texture(2,3, sf::Vector2f(32,32));
            if (player.getDirection() == "D") update_texture(0,0, sf::Vector2f(32,32));
            if (player.getDirection() == "U") update_texture(0,1, sf::Vector2f(32,32));
        }
        if(!is_talking){

//IMPLEMENTER LES DEPLACEMENT DU NPC
        unsigned int dir = std::rand()%4;
        if (dir == 0) update_texture(0,2, sf::Vector2f(32,32));
        if (dir == 1) update_texture(2,3, sf::Vector2f(32,32));
        if (dir == 2) update_texture(0,0, sf::Vector2f(32,32));
        if (dir == 3) update_texture(0,1, sf::Vector2f(32,32));
        // // std::cout << "is_not_talking" << std::endl;
        //     float speed = 32.f;
        //     int moveDelay = 1000;
        //     if(elapsed.asMilliseconds() >= moveDelay){
        //     if (elapsed.asMilliseconds() >= 4*moveDelay/4 && elapsed.asMilliseconds() < 5*moveDelay/4){
        //         move(speed, 0.f); update_texture(2,3, sf::Vector2u(32,32));
        //         elapsed += deltaTime;   
        //     }
        //     // else {elapsed += deltaTime;}
        //     if (elapsed.asMilliseconds() >= 5*moveDelay/4 && elapsed.asMilliseconds() < 6*moveDelay/4){
        //         move(0.f, -speed); update_texture(0,0, sf::Vector2u(32,32));
        //         elapsed += deltaTime;
        //     }
        //     // else {elapsed += deltaTime;}
        //     if (elapsed.asMilliseconds() >= 6*moveDelay/4 && elapsed.asMilliseconds() < 7*moveDelay/4){
        //         move(-speed, 0.f); update_texture(0,2, sf::Vector2u(32,32));
        //         elapsed += deltaTime;
        //     }
        //     // else {elapsed += deltaTime;}
        //     if (elapsed.asMilliseconds() >= 7*moveDelay/4 && elapsed.asMilliseconds() < 8*moveDelay/4){
        //         move(0.f, speed); update_texture(0,1, sf::Vector2u(32,32));
        //         elapsed += deltaTime;
        //     }
        //     if (elapsed.asMilliseconds()>= 2*moveDelay) elapsed = sf::Time::Zero;
        // }
        // else{
        //     elapsed += deltaTime;
        // }
        }
    }

    void NPC::update_texture(unsigned int u,unsigned int v, sf::Vector2f tileSize){
        // std::cout << u << "," << tileSize.x << "," << tileSize.y << std::endl;
        m_vertices[0].texCoords = sf::Vector2f(u * tileSize.x, v*tileSize.y);
        m_vertices[1].texCoords = sf::Vector2f((u + 1) * tileSize.x, v*tileSize.y);
        m_vertices[2].texCoords = sf::Vector2f((u + 1) * tileSize.x, (v+1)*tileSize.y);
        m_vertices[3].texCoords = sf::Vector2f(u * tileSize.x, (v+1)*tileSize.y);
        }

    void NPC::sendMessage(sf::RenderWindow& window, sf::FloatRect ViewRect, sf::Font& font, std::string dialogue){
        //std::cout << window.getSize().x << ";" << window.getSize().y << std::endl;
        sf::Text message;
        message.setFont(font);
        message.setString(dialogue);
        message.setCharacterSize(0.1 * ViewRect.width);
        message.setFillColor(sf::Color::Black);

        float rectangleWidth = ViewRect.width;
        float rectangleHeight = 0.153 * ViewRect.height;
        float rectangleX = ViewRect.left;
        float rectangleY = ViewRect.height - rectangleHeight;

        sf::RectangleShape blueRectangle(sf::Vector2f(rectangleWidth, rectangleHeight));
        sf::RectangleShape blueRectangleTop(sf::Vector2f(rectangleWidth, 0.0093*ViewRect.height));
        sf::RectangleShape blueRectangleLeft(sf::Vector2f(0.0093*ViewRect.height, rectangleHeight));
        sf::RectangleShape blueRectangleRight(sf::Vector2f(0.0093*ViewRect.height, rectangleHeight));
        sf::RectangleShape blueRectangleBot(sf::Vector2f(rectangleWidth, 0.0093*ViewRect.height));
        std::cout << rectangleX << ";" << rectangleY << ";" << rectangleWidth << ";" << rectangleHeight << ";" << std::endl;
        blueRectangle.setPosition(rectangleX, rectangleY);
        blueRectangle.setFillColor(sf::Color(200, 200, 200, 100));
        blueRectangleTop.setPosition(rectangleX, rectangleY);
        blueRectangleTop.setFillColor(sf::Color(50, 50, 50, 200));
        blueRectangleLeft.setPosition(rectangleX, rectangleY);
        blueRectangleLeft.setFillColor(sf::Color(50, 50, 50, 200));
        blueRectangleRight.setPosition(rectangleWidth - 0.0093*ViewRect.height, rectangleY);
        blueRectangleRight.setFillColor(sf::Color(50, 50, 50, 200));
        blueRectangleBot.setPosition(rectangleX, ViewRect.height - 0.0093*ViewRect.height);
        blueRectangleBot.setFillColor(sf::Color(50, 50, 50, 200));
        message.setPosition(rectangleX + 0.0156 * ViewRect.width, rectangleY + 0.0088* ViewRect.width);
        window.draw(blueRectangle);
        window.draw(blueRectangleTop);
        window.draw(blueRectangleLeft);
        window.draw(blueRectangleRight);
        window.draw(blueRectangleBot);
        window.draw(message);
        // std::cout << "ok" << std::endl;
    }