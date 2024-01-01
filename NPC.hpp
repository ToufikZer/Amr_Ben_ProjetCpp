// NPC.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Answer.hpp"

class NPC : public Player{
public:
    NPC(const std::string& texturePath, float pos_x, float pos_y, std::vector<std::string> dialogue, std::string moves,std::vector<Answer> AnswerVector, int type_of_pnj);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(Player& player, const sf::Time &deltaTime, unsigned int map_width, unsigned int map_height, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles);

    void update_texture(unsigned int u,unsigned int v, sf::Vector2f tileSize);

    void sendMessage(sf::RenderWindow& window, sf::Event& event,sf::FloatRect ViewRect, sf::Font& font, int currentMessage);

    sf::FloatRect getGlobalBounds() const {
        return getTransform().transformRect(m_vertices.getBounds());
    }

    void setIsTalking(bool value){
        is_talking = value;
    }

    void setCurrentAnswer(unsigned int value){
        current_answer = value;
    }

    bool getIsAsking(){
        return is_asking;
    }

    bool getIsTalking(){
        return is_talking;
    }

    unsigned int getCurrentAnswer(){
        return current_answer;
    }

    std::vector<std::string>& getDialogue(){
        return dialogue;
    }

    std::string getTexturePath() {
        return TexturePath;
    }

    sf::Vector2u getCurrentPos();

    float& getDelay(){
        return delay;
    }

    void setPlayBool(bool value){
        playsound = value;
    }

    std::vector<Answer> getAnswerVector(){
        return AnswerVector;
    }

    void play_voice();
    void stop_voice();
    void play_toctoc();
private:
    sf::SoundBuffer buffer;
    sf::Sound npc_sound;
    sf::Time elapsed;  // Temps écoulé depuis la dernière mise à jour
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    sf::Vector2u current_pos;
    std::string direction;
    std::vector<std::string> dialogue;
    std::vector<Answer> AnswerVector;
    std::string moves;
    int current_move = 0;
    float delay = 0;
    bool is_talking;
    bool is_asking;
    unsigned int current_answer;
    bool playsound = true;
    std::string TexturePath;

    void draw_answer(sf::RenderWindow& window, sf::Event& event, sf::Font& font, float rectangleX, float rectangleWidth, float rectangleY, float rectangleHeight, unsigned int current_answer);
    void drawTriangle(sf::RenderWindow& window, float edge, float pos_x, float pos_y);
    bool collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs,Player player, std::vector<Obstacle> obstacles);
};
