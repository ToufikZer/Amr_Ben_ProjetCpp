// NPC.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class NPC : public Player{
public:
    NPC(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y, std::vector<std::string> dialogue);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Vector2u getCurrentPos();

    void update(Player& player, const sf::Time &deltaTime, unsigned int map_width, unsigned int map_height, std::vector<std::vector<int>> plan);

    void update_texture(unsigned int u,unsigned int v, sf::Vector2f tileSize);

    void sendMessage(sf::RenderWindow& window,sf::FloatRect ViewRect, sf::Font& font, std::string dialogue);

    void setIsTalking(bool value){
        is_talking = value;
    }
    std::vector<std::string> const& getDialogue() const {
        return dialogue;
    }
private:
    sf::Time elapsed;  // Temps écoulé depuis la dernière mise à jour
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    sf::Vector2u current_pos;
    std::string direction;
    std::vector<std::string> dialogue;
    bool is_talking = false;
};
