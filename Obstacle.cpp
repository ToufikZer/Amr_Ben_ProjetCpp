#include "Obstacle.hpp"
#include "Player.hpp"
#include "iostream"

unsigned int tile_size_obstacle = TILESIZE;
float ftile_size_obstacle = static_cast<float> (TILESIZE);


// Obstacle::Obstacle() : 
//     ChangeTile1(sf::Vector2f(200,200)),
//     ChangeTile2(sf::Vector2f(200,200))
//     {

// }

Obstacle::Obstacle(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y, sf::Vector2u changeTile1, sf::Vector2u changeTile2, std::string direction_to_enter) :
    ChangeTile1(changeTile1),
    ChangeTile2(changeTile2),
    is_open(false),
    can_enter(false),
    direction_to_enter(direction_to_enter)
    {
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
        std::exit(-1);
    }

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(m_texture.getSize().x / 3, 0.f);
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x / 3, m_texture.getSize().y);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x / 3, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x / 3, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y);

    setPosition(pos_x * ftile_size_obstacle, pos_y * ftile_size_obstacle);
}

Obstacle::Obstacle(const std::string& texturePath, unsigned int pos_x, unsigned int pos_y, sf::Vector2u changeTile1, std::string direction_to_enter) :
    ChangeTile1(changeTile1),
    is_open(false),
    can_enter(false),
    direction_to_enter(direction_to_enter)
    {
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
        std::exit(-1);
    }

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(m_texture.getSize().x / 3, 0.f);
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x / 3, m_texture.getSize().y);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x / 3, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x / 3, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y);

    setPosition(pos_x * ftile_size_obstacle, pos_y * ftile_size_obstacle);
}

void Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

void Obstacle::update(Player& player, const sf::Time &deltaTime){
    unsigned int u = 0;
    if(player.getCurrentPos().x == ChangeTile1.x && player.getCurrentPos().y == ChangeTile1.y) {u = 1; is_open = true;}
    else if(player.getCurrentPos().x == ChangeTile2.x && player.getCurrentPos().y == ChangeTile2.y) {u = 2; is_open = true;}
    else is_open = false;
    if (player.getDirection() == direction_to_enter && is_open) {
        can_enter = true;
    }
    else can_enter = false;
    update_texture(u);
}

void Obstacle::update_texture(unsigned int u){
    m_vertices[0].texCoords = sf::Vector2f(u * m_texture.getSize().x / 3, 0.f);
    m_vertices[1].texCoords = sf::Vector2f((u + 1) * m_texture.getSize().x / 3, 0.f);
    m_vertices[2].texCoords = sf::Vector2f((u + 1) * m_texture.getSize().x / 3, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(u * m_texture.getSize().x / 3, m_texture.getSize().y);
}