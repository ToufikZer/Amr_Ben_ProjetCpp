#include "NPC.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include <cstdlib>
#include <ctime>
#include <cstring>

unsigned int tile_size_npc = TILESIZE;
float ftile_size_npc = static_cast<float> (TILESIZE);

    NPC::NPC(const std::string& texturePath, float pos_x, float pos_y, std::vector<std::string> dialogue, std::string moves): 
    Player(texturePath, pos_x, pos_y, 0),
    current_pos(pos_x,pos_y),
    dialogue(dialogue),
    moves(moves),
    is_talking(false) {
        if (!m_texture.loadFromFile(texturePath)) {
            std::cerr << "Erreur lors du chargement de la texture" << std::endl;
            std::exit(-1);
        }

        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(4);

        m_vertices[0].position = sf::Vector2f(0.f, 0.f);
        m_vertices[1].position = sf::Vector2f(m_texture.getSize().x /3, 0.f);
        m_vertices[2].position = sf::Vector2f(m_texture.getSize().x/3, m_texture.getSize().y/4);
        m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y/4);

        m_vertices[0].texCoords = sf::Vector2f(0.f, ftile_size_npc);
        m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x/3, ftile_size_npc);
        m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x/3, ftile_size_npc + m_texture.getSize().y/4);
        m_vertices[3].texCoords = sf::Vector2f(0.f, ftile_size_npc + m_texture.getSize().y/4);

        m_vertices[0].color = sf::Color::White;
        m_vertices[1].color = sf::Color::White;
        m_vertices[2].color = sf::Color::White;
        m_vertices[3].color = sf::Color::White;
        setPosition(pos_x*ftile_size_npc,pos_y*ftile_size_npc);

    }

    sf::Vector2u NPC::getCurrentPos(){
    return current_pos;
}
    void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform(); 
        states.texture = &m_texture; 
        target.draw(m_vertices, states);
    }
bool NPC::collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs,Player player, std::vector<Obstacle> obstacles){
        if (plan[(position.y)][(position.x)] != 0) return true;
        if (collision_npcs(position, NPCs)) return true;
        if (collision_obstacles(position, obstacles)) return true;
        if ((position.x == player.getCurrentPos().x && position.y == player.getCurrentPos().y)) return true;
    return false;
}

    void NPC::update(Player& player,const sf::Time& deltaTime, unsigned int map_width, unsigned int map_height, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles) {
        int moveDelay = 500;
        sf::Vector2u new_position;
        float speed = ftile_size_npc;
        if (is_talking){
            if (player.getDirection() == 0) update_texture(0,2, sf::Vector2f(ftile_size_npc,ftile_size_npc));
            if (player.getDirection() == 1) update_texture(2,3, sf::Vector2f(ftile_size_npc,ftile_size_npc));
            if (player.getDirection() == 2) update_texture(0,1, sf::Vector2f(ftile_size_npc,ftile_size_npc));
            if (player.getDirection() == 3) update_texture(0,0, sf::Vector2f(ftile_size_npc,ftile_size_npc));
        }
        if(!is_talking){

            if (current_move == moves.size()){
                current_move = 0;
            }
            char movement = moves[current_move];

            if(elapsed.asMilliseconds() >= moveDelay){
                if (movement == 'R'){
                    new_position.x = (current_pos.x + 1); 
                    new_position.y = current_pos.y;
                    if (in_map(map_width, map_height, new_position) && !collision(new_position, plan,NPCs, player, obstacles)){
                    move(speed, 0.f); 
                    current_pos.x += 1;
                    current_move += 1;
                } 
                    update_texture(2,3, sf::Vector2f(m_texture.getSize().x /3,m_texture.getSize().x /4));

                    elapsed = sf::Time::Zero;
                }   
                else if (movement == 'U'){
                    new_position.x = (current_pos.x); 
                    new_position.y = current_pos.y - 1;
                    if (in_map(map_width, map_height, new_position) && !collision(new_position, plan,NPCs, player, obstacles)){
                    move(0.f, -speed); 
                    current_pos.y -= 1;
                    current_move += 1;
                    } 
                    update_texture(0,0, sf::Vector2f(m_texture.getSize().x /3,m_texture.getSize().x /4));
                    elapsed = sf::Time::Zero;
                }
                else if (movement == 'L'){
                    new_position.x = (current_pos.x - 1); 
                    new_position.y = current_pos.y;
                    if (in_map(map_width, map_height, new_position) && !collision(new_position, plan,NPCs, player, obstacles)){
                    move(-speed, 0.f); 
                    current_pos.x -= 1;
                    current_move += 1;
                    } 
                    update_texture(0,2, sf::Vector2f(m_texture.getSize().x /3,m_texture.getSize().x /4));
                    elapsed = sf::Time::Zero;
                }
                else if (movement == 'D'){
                    new_position.x = (current_pos.x); 
                    new_position.y = current_pos.y +1;
                    if (in_map(map_width, map_height, new_position) && !collision(new_position, plan,NPCs, player, obstacles)){
                    move(0.f, speed); 
                    current_pos.y += 1;
                    current_move += 1;
                    }  
                    update_texture(0,1, sf::Vector2f(m_texture.getSize().x /3,m_texture.getSize().x /4));
                    elapsed = sf::Time::Zero;
                }
            }
        else{
            elapsed += deltaTime;
        }
    }
    }
    void NPC::update_texture(unsigned int u,unsigned int v, sf::Vector2f tileSize){
        m_vertices[0].texCoords = sf::Vector2f(u * tileSize.x, v*tileSize.y);
        m_vertices[1].texCoords = sf::Vector2f((u + 1) * tileSize.x, v*tileSize.y);
        m_vertices[2].texCoords = sf::Vector2f((u + 1) * tileSize.x, (v+1)*tileSize.y);
        m_vertices[3].texCoords = sf::Vector2f(u * tileSize.x, (v+1)*tileSize.y);
        }

    void NPC::sendMessage(sf::RenderWindow& window, sf::FloatRect ViewRect, sf::Font& font, std::string dialogue){

        sf::Text message;
        message.setFont(font);
        message.setString(dialogue);
        message.setCharacterSize(0.05 * ViewRect.width);
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
        if (playsound) npc_sound.play();
        else{
            npc_sound.play();
            npc_sound.stop();
        }
        delay += 2;
}