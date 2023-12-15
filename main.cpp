// main.cpp
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include <vector>
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "Tilemap");
    sf::FloatRect Visible_Area(0,0,512,512);
    sf::Clock clock;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return -1;
    }

    const int level[] = {
        0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
        0,1,1,1,1,1,1,0,0,0,0,2,0,0,0,0,
        1,1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,
        0,1,0,0,2,3,3,3,3,0,1,1,1,0,0,0, // modem limeaire idéoriginel
        0,1,1,0,3,3,3,0,0,0,1,1,1,2,0,0,
        0,0,1,0,3,0,2,2,0,0,1,1,1,1,2,0,
        2,0,1,0,3,0,2,2,2,0,1,1,1,1,1,1,
        0,0,1,0,3,2,2,2,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,0,0,0,0,2,0,0,0,0,
        1,1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,
        0,1,0,0,2,0,3,3,3,0,1,1,1,0,0,0,
        0,1,1,0,3,3,3,0,0,0,1,1,1,2,0,0,
        0,0,1,0,3,0,2,2,0,0,1,1,1,1,2,0,
        2,0,1,0,3,0,2,2,2,0,1,1,1,1,1,1,
        0,0,1,0,3,2,2,2,0,0,0,0,1,1,1,1,
    };

    TileMap map(sf::Vector2u(16, 16));
    if (!map.load("texture/texture_decor/tileset.png", sf::Vector2u(32.f, 32.f), level, map.getWidth(), map.getHeight()))
        return -1;

    Player player("texture/texture_char/char_tileset.png", 2, 3);
    sf::View view1(sf::Vector2f(player.getPosition().x + 16.f, player.getPosition().y + 16.f), sf::Vector2f(200, 200));
    NPC npc1("texture/texture_npc/npcpkmn.png", 5, 3, {"Salut","test","caca"});
    NPC npc2("texture/texture_npc/npcpkmn.png", 0, 8, {"Salut2","pioupiou","hello!"});

    std::vector<NPC> NPCs;
    NPCs.push_back(npc1);
    NPCs.push_back(npc2);

    window.setKeyRepeatEnabled(false);
    bool is_talking = false;
    NPC* npc_that_was_talking = nullptr;
    int current_message = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                view1.setSize(event.size.width,event.size.height);
            }
            
            // Gestion de l'événement clavier Pressed
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                {
                    for (NPC& npc : NPCs) {
                        if (!is_talking && player.is_looking_at(npc))
                        {
                            std::cout << "caca1"<<current_message << std::endl;
                            std::cout << "1" << std::endl;
                            is_talking = true;
                            npc.setIsTalking(true);
                            npc.update(player, clock.getElapsedTime(), map, level);
                            npc_that_was_talking = &npc;
                            break;
                        }
                    else if((&npc == npc_that_was_talking) && (is_talking) && (current_message < npc.getDialogue().size() - 1)){
                        std::cout << "2" << std::endl;
                        current_message += 1;
                        std::cout << "caca2"<<current_message << std::endl;
                        break;
                    }
                    else {
                    std::cout << "caca3" <<current_message << std::endl;
                    std::cout << "3" << std::endl;
                    if (npc_that_was_talking != nullptr){
                    if (&npc == npc_that_was_talking) {
                        is_talking = false;
                        current_message = 0;
                        npc_that_was_talking->setIsTalking(false);
                    }
                    }
                    }
                }
                }
                if (event.key.code == sf::Keyboard::P)
                {
                    window.create(sf::VideoMode(800,600),"My window");
                }
            }
        }
        //std::cout << npc_that_was_talking->getDialogue() << std::endl;

        sf::Time deltaTime = clock.restart();
        window.clear();
        window.draw(map);
        player.update(deltaTime, map, view1, level, NPCs, is_talking);
        // window.setView(view1);
        sf::FloatRect ViewRect(0,0,512,512) ; //view1.getViewport();
        window.draw(player);
        for (NPC &npc : NPCs)
        {
            window.draw(npc);
            npc.update(player, deltaTime, map, level);
            if (is_talking && &npc == npc_that_was_talking) {
            npc.sendMessage(window, ViewRect, font, npc.getDialogue()[current_message]); 
            //std::cout << npc_that_was_talking->getDialogue()[current_message] << std::endl;
            }
        }

        window.display();
    }

    return 0;
}
