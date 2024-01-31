// Player.cpp
#include "EnnemiBagarre.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cstdlib>

bool last_moveE = true; //true si dernier deplacement à droite, false sinon


EnnemiBagarre::EnnemiBagarre(const std::string& texturePath, float pos_x, float pos_y, float attack_speed, unsigned int degats, int attack_delay, int HP):
    speed(50),
    attack_speed(attack_speed),
    degats(degats),
    attack_delay(attack_delay),
    HP(HP)
    {

    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
        std::exit(-1);
    }
    
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(m_texture.getSize().x/4, 0.f);
    m_vertices[2].position = sf::Vector2f(m_texture.getSize().x/4, m_texture.getSize().y/2);
    m_vertices[3].position = sf::Vector2f(0.f, m_texture.getSize().y/2);

    m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x/4, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_texture.getSize().x/4, m_texture.getSize().y/2);
    m_vertices[3].texCoords = sf::Vector2f(0.f, m_texture.getSize().y/2);

    setPosition(pos_x, pos_y);
}

void EnnemiBagarre::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}


Projectile EnnemiBagarre::tir(unsigned int degats, float vitesse, sf::Vector2f position, std::string direction){ //l'ennemi tire
    return Projectile(vitesse, degats, position, direction, "texture/texture_obstacle/proj_bas.png", 0);
}


bool EnnemiBagarre::collision(Projectile& proj){ //détecte la collision du tir du joueur (cf classe PlayerBagarre) avec l'ennemi et diminue les point de vie (HP) de l'ennemi
    if(proj.getCible() == 1){
        //Vise l'ennemi
            if (sf::FloatRect(sf::Vector2f(proj.getPosition().x + 10.f, proj.getPosition().y + 4.f), sf::Vector2f(10.f, 24.f)).intersects(getHitbox()))
            {
                HP -= proj.getDegats();
                m_vertices[0].color = sf::Color::Red;
                m_vertices[1].color = sf::Color::Red;
                m_vertices[2].color = sf::Color::Red;
                m_vertices[3].color = sf::Color::Red;
                return true;
            }
            else{
                m_vertices[0].color = sf::Color::White;
                m_vertices[1].color = sf::Color::White;
                m_vertices[2].color = sf::Color::White;
                m_vertices[3].color = sf::Color::White;
            }
    }
    return false;
}


void EnnemiBagarre::update(const sf::Time& deltaTime, unsigned int map_width, unsigned int map_height, PlayerBagarre& player){
            deplacer(deltaTime, map_width, map_height, player);
            
            for(Projectile& proj:projs_ennemi){
                proj.update(deltaTime, map_height);
                if (player.collision(proj)) {proj.setDeleteIt(true);}
                if (proj.getDeleteIt()) projs_ennemi.erase(projs_ennemi.begin());
            }

            if (elapsed.asMilliseconds() > attack_delay){
                projs_ennemi.push_back(tir(degats, attack_speed, sf::Vector2f(getPosition().x + (rand() % 40), getPosition().y + 10), "bas"));
                elapsed = sf::Time::Zero;
            }
            else{
                elapsed += deltaTime;
            }
}

void EnnemiBagarre::deplacer(const sf::Time& deltaTime, unsigned int map_width, unsigned int map_height, PlayerBagarre& player){ //Déplacement automatique de l'ennemi qui va constamment du coté ou se trouve le joueur
    if (player.getPosition().x > getPosition().x + 10.f) { 
        if(!out_map(map_width, map_height, sf::Vector2f(getPosition().x + speed* deltaTime.asSeconds(), getPosition().y))){
                move(speed * deltaTime.asSeconds(), 0.f);
                update_texture(0, (int)getPosition().x / 10 % 4);
                last_moveE = true;
        }
    }
    else if (player.getPosition().x < getPosition().x - 10.f) {
        if(!out_map(map_width, map_height, sf::Vector2f(getPosition().x - speed* deltaTime.asSeconds(), getPosition().y))){
                move(-speed * deltaTime.asSeconds(), 0.f);
                update_texture(1, (int)getPosition().x / 10 % 4);
                last_moveE = false;
        }
    }
    else {
        if(last_moveE)
            update_texture(0, 0);
        else{
            update_texture(1,0);
        }
    }
}

void EnnemiBagarre::update_texture(unsigned int u, unsigned int i) {
    m_vertices[0].texCoords = sf::Vector2f((i) * m_texture.getSize().x/4, (u) * m_texture.getSize().y/2);
    m_vertices[1].texCoords = sf::Vector2f((i+1) * m_texture.getSize().x/4, (u) * m_texture.getSize().y/2);
    m_vertices[2].texCoords = sf::Vector2f((i+1) * m_texture.getSize().x/4, (u+1) * m_texture.getSize().y/2);
    m_vertices[3].texCoords = sf::Vector2f((i) * m_texture.getSize().x/4, (u+1) * m_texture.getSize().y/2);
}

bool EnnemiBagarre::out_map(unsigned int map_width, unsigned int map_height, sf::Vector2f position) { //détecte si l'ennemi est au bord de la map pour éviter qu'il en sorte
    if (position.x >= map_width - m_texture.getSize().x /4 || position.x < 0.f)
        return true;
    return false;
}