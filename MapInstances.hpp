#pragma once

#include "iostream"
#include "Map.hpp"
#include "MapIndoors.hpp"
#include "Answer.hpp"
#include <SFML/Audio.hpp>

#define MAP1 Map({{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},\
                    {1,1,1,1,1,1,1,0,0,0,0,2,0,0,0,1},\
                    {1,1,0,0,0,0,0,0,3,3,3,3,3,3,3,1},\
                    {1,1,0,0,2,3,3,3,3,0,1,1,1,0,0,1},\
                    {1,1,1,0,3,3,3,0,0,0,1,1,1,2,0,1},\
                    {1,0,1,0,3,0,2,2,0,0,1,1,1,1,2,1},\
                    {1,0,1,0,3,0,2,2,2,0,1,1,1,1,1,1},\
                    {0,0,1,0,3,2,2,2,0,0,0,0,1,1,1,0},\
                    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0},\
                    {1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1},\
                    {1,1,0,0,0,0,0,0,3,0,3,3,3,3,3,1},\
                    {1,1,0,0,2,0,3,3,3,0,1,1,1,0,0,1},\
                    {1,1,1,0,3,3,3,0,0,0,1,1,1,2,0,1},\
                    {1,0,1,0,3,0,2,2,0,0,1,1,1,1,2,1},\
                    {1,0,1,0,3,0,2,2,2,0,1,1,1,1,1,1},\
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 8, 13, {"Salut", "test", "caca"},"RULD",{},0)), \
                     (NPC("texture/texture_npc/npcpkmn.png", 1, 8, {"Salut2", "pioupiou", "hello!"},"RRUUUDDDLL",{},0))}, \
                    "sound/music/music1.ogg")

#define MAP2 Map({{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, \
                    {1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1}, \
                    {1,0,0,0,0,0,0,0,3,3,3,3,3,3,3,1}, \
                    {1,0,0,0,2,3,3,3,3,0,0,0,0,0,0,1}, \
                    {1,0,0,0,3,3,3,0,0,0,0,0,0,2,0,1}, \
                    {1,0,0,0,3,0,2,2,0,0,0,0,0,0,2,1}, \
                    {1,0,0,0,3,0,2,2,2,0,0,0,0,0,0,1}, \
                    {0,0,0,0,3,2,2,2,0,0,0,0,0,0,0,1}, \
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, \
                    {1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1}, \
                    {1,0,0,0,0,0,0,0,3,3,3,3,3,3,3,1}, \
                    {1,0,0,0,2,0,3,3,3,0,0,0,0,0,0,1}, \
                    {1,0,0,0,3,3,3,0,0,0,0,0,0,2,0,1}, \
                    {1,0,0,0,3,0,2,2,0,0,0,0,0,0,2,1}, \
                    {1,0,0,0,3,0,2,2,2,0,0,0,0,0,0,1}, \
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 9, 9, {"Salut", "test", "caca","retest"},"UUUUDDDD",{},0)), \
                     (NPC("texture/texture_npc/npcpkmn.png", 0, 3, {"Salut2", "pioupiou", "hello!"},"RULD",{},0))}, \
                    {Obstacle("texture/texture_obstacle/Crous.png", 9, 1, sf::Vector2u(10,7), sf::Vector2u(12,7),2, 1)}, \
                    "sound/music/music2.ogg")



#define MAP3 Map({{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},\
                    {1,2,2,2,2,2,2,0,0,0,0,2,0,0,0,1},\
                    {1,2,0,0,0,0,0,0,3,3,3,3,3,3,3,1},\
                    {1,2,0,0,1,3,3,3,3,0,0,0,0,0,0,1},\
                    {1,2,2,0,3,3,3,0,0,0,0,0,0,0,0,1},\
                    {1,0,1,0,3,0,1,1,0,0,0,0,0,0,1,1},\
                    {1,0,2,0,3,0,1,1,0,0,0,0,0,0,1,1},\
                    {1,0,2,0,3,2,1,1,0,0,0,0,0,0,2,2},\
                    {1,0,0,0,0,0,2,1,0,0,0,0,0,0,0,2},\
                    {1,1,1,1,1,0,2,0,0,0,0,0,0,0,0,1},\
                    {1,2,0,0,0,0,0,0,3,0,3,3,3,3,3,1},\
                    {1,1,0,0,1,0,3,3,3,0,1,1,2,0,0,1},\
                    {1,2,2,0,3,3,3,0,0,0,2,1,1,1,0,1},\
                    {1,0,1,0,3,0,1,2,0,0,2,2,2,1,1,1},\
                    {1,0,0,0,3,0,2,2,2,0,2,1,1,1,1,1},\
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 8, 13, {"Voulez vous manger avec moi?","QUESTION", "QUOI, COMMENT CA NON", "CETAIT UNE PIZZA AU CACA","1","2"},"RUUULRRDULLRDDDL",{Answer("yes",true,0),Answer("no",false,1)},0)), \
                     (NPC("texture/texture_npc/npcpkmn.png", 1, 8, {"Salut2", "pioupiou", "hello!", "okok"},"RRUUUDDDLL",{},0))}, \
                     {Obstacle("texture/texture_obstacle/Crous.png", 9, 1, sf::Vector2u(10,7), sf::Vector2u(12,7),2, 3)}, \
                    "sound/music/music1.ogg")

#define MAP4 Map({{3,3,3,3,3,3,3},\
                    {3,0,0,0,0,0,3},\
                    {3,0,0,0,0,0,3},\
                    {3,0,0,0,0,0,3},\
                    {3,0,0,0,0,0,3},\
                    {3,0,0,0,0,0,3},\
                    {3,3,3,0,3,3,3}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 5, 5, {"Voulez vous manger avec moi?", "QUOI, COMMENT CA NON", "CETAIT UNE PIZZA AU CACA"},"RUUULRRDULLRDDDL",{},0))}, \
                    {Obstacle("texture/texture_obstacle/door.png", 3, 6, sf::Vector2u(3,5),3, 2)}, \
                    "sound/music/music1.ogg")

#define MAP5 MapIndoors("GARE", \
                        "texture/texture_decor/decorgare.jpg", \
                        {(NPC("texture/texture_npc/npc.png", 10, 1, {"Voulez vous manger avec moi?", "QUOI, COMMENT CA NON", "CETAIT UNE PIZZA AU CACA"},"RUUULRRDULLRDDDL",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 16, 15, 0))}, \
                        "sound/music/music2.ogg",4,10)

#define MAP6 MapIndoors("MARIO", \
                        "texture/texture_decor/mario.png", \
                        "sound/music/music2.ogg",1,10)

#define MAP7 MapIndoors("CROUS", \
                        "texture/texture_decor/crous.png", \
                        {(NPC("texture/texture_npc/door_invisible.png", 80, 110, {"EXIT"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 350, 110, {"The door seems to be closed"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 565, 110, {"The door seems to be closed"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 840, 110, {"The door seems to be closed"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 80, 400, {"The door seems to be closed"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 350, 400, {"The door seems to be closed"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 565, 400, {"Someone is already posing un classique"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 840, 400, {"The door seems to be closed"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 80, 700, {"Oh, the doors seems to be half-open"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 350, 700, {"The door seems to be closed"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 565, 700, {"The door seems to be closed"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 840, 700, {"CUISINE"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 15, 12, 0)), \
                        (Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 2, 0))}, \
                        "sound/music/music2.ogg",3,250)
                        

#define MAP8 MapIndoors("KITCHEN", \
                        "texture/texture_decor/kitchen.jpg", \
                        {(NPC("texture/texture_obstacle/key.png", 113, 168, {"KEY", "Wow there's keys !!", "Probably one student forgot them there", "Oh, there is something written on it?", "'with great power comes great responsibility'"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 5, 3, 0))}, \
                        "sound/music/music1.ogg",1,60)

#define MAP9 MapIndoors("AIRPORT", \
                        "texture/texture_decor/aeroport.jpg", \
                        {(NPC("texture/texture_npc/npc_airport.png", 326, 143, {"Salut!", "Tu viens d'arriver?", "QUESTION","Je dois te prevenir, les taxis sont en greve", "tu vas devoir prendre les transports", \
                        "Ou bien il y a une agence de location de vehicule qui a ouvert\nTu peux tenter ta chance elle n'est pas loin",  "Il faut que tu prennes a droite, si c'est ferme tu vas\n devoir faire un detour par le haut!"},"",{Answer("yes",true,0),Answer("no",false,1),Answer("maybe",false,2)},1)), \
                        (NPC("texture/texture_npc/valise.png", 476, 170, {"KNIFE", "Il y a un couteau dans la valise", "Ca pourrait etre utile, on sait jamais..."},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 3, 0))}, \
                        "sound/music/music1.ogg",1,100)
                        

