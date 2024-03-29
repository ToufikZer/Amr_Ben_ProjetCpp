#include "Fraudeur.hpp"

#include "TileMap.hpp"
#include "Obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Fraudeur::Fraudeur(const std::string &texturePath, unsigned int pos_x, unsigned int pos_y, Inventory inventaire) :
    crash(false),
    speed(5),
    invincible(false),
    inventaire(inventaire)
    {

    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
        std::exit(-1);
    }
    
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(m_texture.getSize().x /4, 0.f);
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x/4, m_texture.getSize().y);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x/4, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x/4, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y);

    setPosition(pos_x * 64.f, pos_y * 64.f);

    initialize_crash();
}

void Fraudeur::initialize_crash(){
    CrashText.rotate(90);
    CrashText.setStyle(sf::Text::Bold);
    CrashText.setString("Entrer pour revenir, R pour recommencer");
    CrashText.setFillColor(sf::Color(250,30,30,250));
    CrashText.setCharacterSize(30);
}

void Fraudeur::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

bool Fraudeur::collision_obstacles(sf::Vector2f position, std::vector<Obstacle> obstacles){ //détecte la collision du joueur avec un obstacle 
    for (Obstacle& obstacle : obstacles){
        if (sf::FloatRect(sf::Vector2f(position.x + m_texture.getSize().x/12, position.y+m_texture.getSize().y/8), 
            sf::Vector2f(m_texture.getSize().x*2/12, m_texture.getSize().y*6/8)).intersects(obstacle.getGlobalBounds()))
        {
            if (obstacle.getId() == 0) return true;
            else{
                if (!invincible) return true;
            }
        }
    }
    return false;
}


void Fraudeur::update(const sf::Time& deltaTime, sf::Font& font, unsigned int map_width, unsigned int map_height, 
                       sf::View& view, std::vector<Obstacle> obstacles){

    elapsed += deltaTime;

    if(!collision_obstacles(getPosition(),obstacles ) && !crash){
        float speedIncrease = 0.02;
        move(speed ,0.f);
        if (speed < 12 ) speed += speedIncrease;

        deplacer_vert();
        deplacer_horiz(map_width, map_height);   
    }
    else{
        CrashText.setFont(font);
        crash = true;
        if (speed > 0)
        {
            move(speed,0.f);
            speed -= 1;
            rotate(5);
        }
    }
    view.setCenter(getPosition().x + 0.35*view.getSize().x, map_height *16 + 160);
}


void Fraudeur::draw_crash(sf::RenderWindow& window){ // animation en cas de crash (collision avec obstacle)
    if (crash) {
        CrashText.setPosition(sf::Vector2f(getPosition().x + 150.f, getPosition().y - 200.f));
        window.draw(CrashText);
    }
}


void Fraudeur::update_texture(unsigned int u) {
    m_vertices[0].texCoords = sf::Vector2f(u * m_texture.getSize().x/4, 0.f);
    m_vertices[1].texCoords = sf::Vector2f((u+1) * m_texture.getSize().x/4, 0.f);
    m_vertices[2].texCoords = sf::Vector2f((u+1) * m_texture.getSize().x/4, m_texture.getSize().y);
    m_vertices[3].texCoords = sf::Vector2f(u * m_texture.getSize().x/4, m_texture.getSize().y);
}


bool Fraudeur::in_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position) {
    if (position.x < map_width * 64 && position.y < (map_height- 1.5) * 64 && position.x >= 0 && position.y >= 96)
        return true;
    else
        return false;
}


void Fraudeur::sauter_anim(){ //animation du saut
    if (elapsed.asMilliseconds() > 200){
        update_texture(3);
    }
    if (elapsed.asMilliseconds() > 350){
        update_texture(2);
    }
    if (elapsed.asMilliseconds() > 500){
        invincible = false;
        update_texture(0);
        elapsed = sf::Time::Zero;
    }
}

void Fraudeur::sauter(){ //permet au joueur de sauter par dessus les obstacles
    if (elapsed.asMilliseconds() > 200){
        invincible = true;
        update_texture(2);
        elapsed = sf::Time::Zero;
    }
}

void Fraudeur::courir_anim(){ //animation du joueur qui court
    if (elapsed.asMilliseconds() % 500 <= 250) update_texture(0);
    else update_texture(1);
}

void Fraudeur::deplacer_vert(){ //gestion du saut 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !invincible){
        sauter();
    }
    else if (invincible){
        sauter_anim();
    }
    else{
        courir_anim();
    }
}

void Fraudeur::deplacer_horiz(unsigned int map_width, unsigned int map_height){ //gestion des déplacements horizontaux du joueur
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (in_map(map_width, map_height, sf::Vector2f(getPosition().x, getPosition().y + 2))){
            move(0,4);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        if (in_map(map_width, map_height, sf::Vector2f(getPosition().x, getPosition().y - 2))){
            move(0,-4);
        }
    }
}

