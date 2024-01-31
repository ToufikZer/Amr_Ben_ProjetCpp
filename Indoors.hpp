// InGame_CarGameplay.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "PlayerIndoors.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "MapIndoors.hpp"
#include "InGame.hpp"
#include "Item.hpp"
#include "Enigme.hpp"

class Indoors : public GameState {
public:
    Indoors(sf::RenderWindow& window, std::string MapName, float pos_player_x, float pos_player_y, Inventory inventaire, std::string objectif_text, bool combat_win);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Event& event);
    GameState* getNextState() ;

private:
    void initialize_maplist();
    void initialize_objectif();

    void event_key(NPC& npc);
    void event_knife(NPC& npc);
    void event_bottes(NPC& npc);

    void event_enigme1();
    void event_enigme2();
    void event_enigme3();
    void event_enigme4();

    void FirstTalk(NPC& npc);
    void LastTalk(NPC& npc);

    void ChooseAnswer(sf::Event& event);
    void EnigmeAnswer(sf::Event& event);

    sf::RenderWindow& window;
    sf::View view;
    sf::Font font;
    sf::Text objectif;
    std::string objectif_text;
    PlayerInDoors player;
    MapIndoors map;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music music;
    std::string BackgroundPath;
    std::string MusicPath;  
    std::vector<Obstacle> obstacles;
    std::vector<NPC> NPCs;
    unsigned int FloorNumber;
    float PlayerSpeed;
    std::vector<MapIndoors> MapList;
    std::string MapName;
    Enigme enigme;

    std::vector<std::string> first_dialogue;
    bool isTalking;
    NPC* npcThatWasTalking;
    unsigned int currentMessage;

    bool back_to_town;
    bool backmenu;
    bool next_town;
    bool kitchen;
    bool exit_concess;
    bool car;
    bool crous;
    bool room;
    bool exit_room;
    bool bagarre;
    bool exit_gare;
    bool combat_win;
    bool enigme_active;
    bool enigme1_done;
    bool enigme2_done;
    bool enigme3_done;
    bool enigme4_done;
    bool fraude;
    bool no_fraude;
    bool labyrinthe;
    bool bagarreFou;
    bool bagarreF;

    void draw_objectif();
    bool has_key(Inventory inventaire);
    bool has_boots(Inventory inventaire);
    bool has_kitchen_knife(Inventory inventaire);
    void executeOption();
};