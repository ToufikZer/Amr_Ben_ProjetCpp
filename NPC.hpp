// NPC.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"
#include "Obstacle.hpp"

class NPC : public Player{
public:
    NPC(const std::string& texturePath, float pos_x, float pos_y, std::vector<std::string> dialogue, std::string moves);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(Player& player, const sf::Time &deltaTime, unsigned int map_width, unsigned int map_height, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs, std::vector<Obstacle> obstacles);

    void update_texture(unsigned int u,unsigned int v, sf::Vector2f tileSize);

    void sendMessage(sf::RenderWindow& window,sf::FloatRect ViewRect, sf::Font& font, std::string dialogue);

    sf::FloatRect getGlobalBounds() const {
        return getTransform().transformRect(m_vertices.getBounds());
    }

    void setIsTalking(bool value){
        is_talking = value;
    }
    std::vector<std::string> const& getDialogue() const {
        return dialogue;
    }
    sf::Vector2u getCurrentPos();

    sf::Sound getSound(){
        return npc_sound;
    }

    float& getDelay(){
        return delay;
    }

    void setPlayBool(bool value){
        playsound = value;
    }

    void play_voice();
private:
    sf::SoundBuffer buffer;
    sf::Sound npc_sound;
    sf::Time elapsed;  // Temps écoulé depuis la dernière mise à jour
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    sf::Vector2u current_pos;
    std::string direction;
    std::vector<std::string> dialogue;
    std::string moves;
    int current_move = 0;
    float delay = 0;
    bool is_talking;
    bool playsound = true;

    bool collision(sf::Vector2u position, std::vector<std::vector<int>> plan, std::vector<NPC> NPCs,Player player, std::vector<Obstacle> obstacles);
};
