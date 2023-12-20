#include "NPC.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include <cstdlib>
#include <ctime>
#include <cstring>

    NPC::NPC(const std::string& texturePath, unsigned int pos_x,unsigned int pos_y, std::vector<std::string> dialogue, std::string moves): 
    Player(texturePath, pos_x, pos_y),
    current_pos(pos_x,pos_y),
    dialogue(dialogue),
    moves(moves),
    is_talking(false) {
        // Charger la texture du joueur
        if (!m_texture.loadFromFile(texturePath)) {
            std::cerr << "Erreur lors du chargement de la texture" << std::endl;
            std::exit(-1);
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

    bool NPC::collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs,Player player){
        for (NPC& npc : NPCs){
            //std::cout << plan[0] << ";" << plan[10] <<std::endl;
        if ((plan[(position.y)][(position.x)] != 0 )
            || 
            (position.x == npc.getCurrentPos().x && position.y == npc.getCurrentPos().y )
            ||
            (position.x == player.getCurrentPos().x && position.y == player.getCurrentPos().y)){
        return true;
        }
        }
        return false;
    }

    // Mettez à jour la position du joueur en fonction des entrées utilisateur
    void NPC::update(Player& player,const sf::Time& deltaTime, unsigned int map_width, unsigned int map_height, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs) {
        int moveDelay = 1000;
        sf::Vector2u new_position;
        float speed = 32.f;
        // std::srand(static_cast<unsigned int>(std::time(nullptr)));   
        if (is_talking){
        // std::cout << "is_talking" << std::endl;
            if (player.getDirection() == "R") update_texture(0,2, sf::Vector2f(32,32));
            if (player.getDirection() == "L") update_texture(2,3, sf::Vector2f(32,32));
            if (player.getDirection() == "D") update_texture(0,0, sf::Vector2f(32,32));
            if (player.getDirection() == "U") update_texture(0,1, sf::Vector2f(32,32));
        }
        if(!is_talking){
//IMPLEMENTER LES DEPLACEMENT DU NPC
        // unsigned int dir = std::rand()%4;
        // if (elapsed.asMilliseconds() >= moveDelay) {
        // if (dir == 0) {update_texture(0,2, sf::Vector2f(32,32)); elapsed = sf::Time::Zero;}
        // if (dir == 1) {update_texture(2,3, sf::Vector2f(32,32)); elapsed = sf::Time::Zero;}
        // if (dir == 2) {update_texture(0,0, sf::Vector2f(32,32)); elapsed = sf::Time::Zero;}
        // if (dir == 3) {update_texture(0,1, sf::Vector2f(32,32)); elapsed = sf::Time::Zero;}
        // }
        // else{
        //     elapsed += deltaTime;
        // }
        // std::cout << "is_not_talking" << std::endl;
            // std::cout << current_move << std::endl;
            if (current_move == moves.size()){
                current_move = 0;
            }
            char movement = moves[current_move];
            // std::cout << movement << std::endl;

            if(elapsed.asMilliseconds() >= moveDelay){
                if (movement == 'R'){
                    new_position.x = (current_pos.x + 1); 
                    new_position.y = current_pos.y;
                    if (in_map(map_width, map_height, new_position) && !collision(new_position, plan,NPCs, player)){
                    move(speed, 0.f); 
                    current_pos.x += 1;
                    current_move += 1;
                } 
                    update_texture(2,3, sf::Vector2f(32,32));
                    // std::cout << "is_not_talking" << std::endl;
                    elapsed = sf::Time::Zero;
                }   
            // else {elapsed += deltaTime;}
                else if (movement == 'U'){
                    new_position.x = (current_pos.x); 
                    new_position.y = current_pos.y - 1;
                    if (in_map(map_width, map_height, new_position) && !collision(new_position, plan,NPCs, player)){
                    move(0.f, -speed); 
                    current_pos.y -= 1;
                    current_move += 1;
                    } 
                    update_texture(0,0, sf::Vector2f(32,32));
                    elapsed = sf::Time::Zero;
                }
            // else {elapsed += deltaTime;}
                else if (movement == 'L'){
                    new_position.x = (current_pos.x - 1); 
                    new_position.y = current_pos.y;
                    if (in_map(map_width, map_height, new_position) && !collision(new_position, plan,NPCs, player)){
                    move(-speed, 0.f); 
                    current_pos.x -= 1;
                    current_move += 1;
                    } 
                    update_texture(0,2, sf::Vector2f(32,32));
                    elapsed = sf::Time::Zero;
                }
            // else {elapsed += deltaTime;}
                else if (movement == 'D'){
                    new_position.x = (current_pos.x); 
                    new_position.y = current_pos.y +1;
                    if (in_map(map_width, map_height, new_position) && !collision(new_position, plan,NPCs, player)){
                    move(0.f, speed); 
                    current_pos.y += 1;
                    current_move += 1;
                    }  
                    update_texture(0,1, sf::Vector2f(32,32));
                    elapsed = sf::Time::Zero;
                }
            }
        else{
            elapsed += deltaTime;
        }
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
        // if (!buffer.loadFromFile("sound/sound/npc_voice.wav")){
        //     std::cerr << "Erreur lors du chargement du son" << std::endl;
        //     std::exit(-1);
        // }
        // npc_sound.setBuffer(buffer);
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
        //std::cout << rectangleX << ";" << rectangleY << ";" << rectangleWidth << ";" << rectangleHeight << ";" << std::endl;
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

    }

void NPC::play_voice(){
    unsigned int num_voice = std::rand()%11 + 1;
    if (!buffer.loadFromFile("sound/sound/npc_voice/npc_voice" + std::to_string(num_voice) + ".wav")){
            std::cerr << "Erreur lors du chargement du son" << std::endl;
            std::exit(-1);
        }
        npc_sound.setBuffer(buffer);
        npc_sound.setPlayingOffset(sf::seconds(delay));
        npc_sound.setVolume(25);
        //std::cout << playsound << std::endl;
        if (playsound) npc_sound.play();
        else{
            npc_sound.play();
            //sf::sleep(sf::seconds(2));
            npc_sound.stop();
        }
        delay += 2;
}