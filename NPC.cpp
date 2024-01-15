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

    NPC::NPC(const std::string& texturePath, float pos_x, float pos_y, std::vector<std::string> dialogue, std::string moves,std::vector<Answer> AnswerVector, int type_of_pnj): 
    Player(texturePath, pos_x, pos_y, 0, Inventory()),
    current_pos(pos_x,pos_y),
    dialogue(dialogue),
    AnswerVector(AnswerVector),
    moves(moves),
    TexturePath(texturePath),
    is_talking(false),
    is_asking(false),
    current_answer(0)
     {
        if (type_of_pnj == 0) {
            if (!m_texture.loadFromFile(texturePath)) {
                std::cerr << "Erreur lors du chargement de la texture" << std::endl;
                std::exit(-1);
            }

            m_vertices.setPrimitiveType(sf::Quads);
            m_vertices.resize(4);

            m_vertices[0].position = sf::Vector2f(0.f, 0.f);
            m_vertices[1].position = sf::Vector2f(m_texture.getSize().x /3, 0.f);
            m_vertices[2].position = sf::Vector2f(m_texture.getSize().x /3, m_texture.getSize().y/4);
            m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y/4);

            m_vertices[0].texCoords = sf::Vector2f(0.f, m_texture.getSize().y/4);
            m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x /3, m_texture.getSize().y/4);
            m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x /3, 2*m_texture.getSize().y/4);
            m_vertices[3].texCoords = sf::Vector2f(0.f, 2*m_texture.getSize().y/4);

            m_vertices[0].color = sf::Color::White;
            m_vertices[1].color = sf::Color::White;
            m_vertices[2].color = sf::Color::White;
            m_vertices[3].color = sf::Color::White;
            setPosition(pos_x*ftile_size_npc,pos_y*ftile_size_npc);
        }

        else if (type_of_pnj == 1) {
            if (!m_texture.loadFromFile(texturePath)) {
                std::cerr << "Erreur lors du chargement de la texture" << std::endl;
                std::exit(-1);
            }

            m_vertices.setPrimitiveType(sf::Quads);
            m_vertices.resize(4);

            m_vertices[0].position = sf::Vector2f(0.f, 0.f);
            m_vertices[1].position = sf::Vector2f(m_texture.getSize().x, 0.f);
            m_vertices[2].position = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
            m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y);

            m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
            m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0.f);
            m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
            m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y);

            m_vertices[0].color = sf::Color::White;
            m_vertices[1].color = sf::Color::White;
            m_vertices[2].color = sf::Color::White;
            m_vertices[3].color = sf::Color::White;
            setPosition(pos_x,pos_y);
        }
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
                    update_texture(2,3, sf::Vector2f(m_texture.getSize().x /3,m_texture.getSize().y /4));

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
                    update_texture(0,0, sf::Vector2f(m_texture.getSize().x /3,m_texture.getSize().y /4));
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
                    update_texture(0,2, sf::Vector2f(m_texture.getSize().x /3,m_texture.getSize().y /4));
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
                    update_texture(0,1, sf::Vector2f(m_texture.getSize().x /3,m_texture.getSize().y /4));
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

    void NPC::sendMessage(sf::RenderWindow& window, sf::Event& event, sf::FloatRect ViewRect, sf::Font& font, int currentMessage){
        if (dialogue[currentMessage] == "QUESTION") {
            is_asking = true;
            currentMessage-- ;    
        }
        else {
            is_asking = false;
        }
        sf::Text message;
        message.setFont(font);
        message.setString(dialogue[currentMessage]);
        message.setCharacterSize(0.05 * ViewRect.height);
        message.setFillColor(sf::Color::Black);

        float rectangleWidth = ViewRect.width;
        float rectangleHeight = 0.153 * ViewRect.height;
        float rectangleX = ViewRect.left;
        float rectangleY = ViewRect.height - rectangleHeight;
        std::cout << rectangleX << ";" << rectangleY <<std::endl;
        if (is_asking) {
            draw_answer(window, event, font, rectangleX, rectangleWidth, rectangleY, rectangleHeight, current_answer);
        }
        sf::RectangleShape TextRectangle(sf::Vector2f(rectangleWidth -2 *0.0093 * ViewRect.height, rectangleHeight - 0.0093 * ViewRect.height));
        TextRectangle.setPosition(rectangleX + 0.0093 * ViewRect.height, rectangleY);
        TextRectangle.setFillColor(sf::Color(200, 200, 200, 100));

        // Définir la bordure du rectangle
        TextRectangle.setOutlineColor(sf::Color(50, 50, 50, 200));  
        TextRectangle.setOutlineThickness(0.0093 * ViewRect.height);  

        window.draw(TextRectangle);

        message.setPosition(rectangleX + 0.0156 * ViewRect.width, rectangleY + 0.0088* ViewRect.width);
        window.draw(message);

    }

void NPC::play_voice(){
    unsigned int num_voice = std::rand()%11 + 1;
    if (!buffer.loadFromFile("sound/sound/npc_voice/npc_voice" + std::to_string(num_voice) + ".wav")){
            std::cerr << "Erreur lors du chargement du son" << std::endl;
            std::exit(-1);
        }
        npc_sound.setBuffer(buffer);
        npc_sound.setVolume(25);
        if (playsound) npc_sound.play();
        else{
            npc_sound.play();
            npc_sound.stop();
        }
}

void NPC::stop_voice(){
    npc_sound.stop();

    npc_sound.resetBuffer();
}

void NPC::play_toctoc(){
    sf::Sound toctoc_sound;
    sf::SoundBuffer buffer_toctoc;
    if (!buffer_toctoc.loadFromFile("sound/sound/toctoc.wav")){
            std::cerr << "Erreur lors du chargement du son" << std::endl;
            std::exit(-1);
        }
        toctoc_sound.setBuffer(buffer_toctoc);
        toctoc_sound.setVolume(25);
        toctoc_sound.play();
        sf::sleep(sf::seconds(0.5));
        
}

void NPC::draw_answer(sf::RenderWindow& window, sf::Event& event, sf::Font& font, float rectangleX, float rectangleWidth, float rectangleY, float rectangleHeight, unsigned int current_answer) {
    sf::RectangleShape answerBox(sf::Vector2f(0.25*rectangleWidth, 0.5*rectangleHeight * AnswerVector.size()));
    answerBox.setPosition(rectangleX + 0.75*rectangleWidth, rectangleY - 0.5*rectangleHeight * AnswerVector.size() );
    answerBox.setFillColor(sf::Color(150,150,150,150)); // Couleur de la case de réponse
    window.draw(answerBox);
    float gap = 0;
    drawTriangle(window,0.15*rectangleHeight,rectangleX + 0.90*rectangleWidth, answerBox.getPosition().y + 2 + current_answer * rectangleHeight / 2);
    for (Answer& answer : AnswerVector){
        sf::Text text(answer.getChoice(), font, rectangleHeight / 3); // Ajustez la taille du texte
        text.setFillColor(sf::Color(0, 0, 0)); // Couleur du texte
        text.setPosition(answerBox.getPosition().x + 5, answerBox.getPosition().y + 1 + gap);
        window.draw(text);
        gap += rectangleHeight / 2;
    }
}

void NPC::drawTriangle(sf::RenderWindow& window, float edge, float pos_x, float pos_y){
    sf::CircleShape triangle(edge, 3);
    triangle.setPosition(pos_x,pos_y);
    triangle.setFillColor(sf::Color::Black);
    triangle.rotate(25.5);
    window.draw(triangle);
}

