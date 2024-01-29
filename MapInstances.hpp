#pragma once

#include "iostream"
#include "Map.hpp"
#include "MapIndoors.hpp"
#include "Answer.hpp"
#include <SFML/Audio.hpp>


#define MAP0 Map({{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 1, 8, {"Y'a beaucoup de touriste ces temps ci,\nc'est a en perdre la tete", "Le nouveau concessionnaire fait des ravages"}, "RUDL",{}, 0)), \
                     (NPC("texture/texture_npc/npcpkmn.png", 10, 13, {"Salut2", "pioupiou", "hello!", "okok"},"RRRRUUULLLLDDD",{},0))}, \
                     {Obstacle("texture/texture_obstacle/aeroport_tile.png", 1, 1, sf::Vector2u(4,7),2, 4),\
                     Obstacle("texture/texture_obstacle/avion.png", 1, 5, 0)}, \
                    "sound/music/music1.ogg")

#define MAP1 Map({{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 8, 13, {"Voulez vous manger avec moi?","QUESTION"},"RUUULRRDULLRDDDL",{Answer("yes",{"YOUHOUUU","Enfin qqn qui accepte!"},0),Answer("no",{"QUOI, COMMENT CA NON", "CETAIT UNE PIZZA AU CACA"},1)},0)), \
                     (NPC("texture/texture_npc/npcpkmn.png", 1, 8, {"Salut2", "pioupiou", "hello!"},"RRUUUDDDLL",{},0))}, \
                    "sound/music/music1.ogg")

#define MAP2 Map({{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 9, 9, {"Salut", "test", "caca","retest"},"UUUUDDDD",{},0)), \
                     (NPC("texture/texture_npc/npcpkmn.png", 0, 3, {"Salut2", "pioupiou", "hello!"},"RULD",{},0))}, \
                    {Obstacle("texture/texture_obstacle/Crous.png", 9, 1, sf::Vector2u(10,7), sf::Vector2u(12,7),2, 1)}, \
                    "sound/music/music2.ogg")



#define MAP3 Map({{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 8, 13, {"Y'a beaucoup de touriste ces temps ci,\nc'est a en perdre la tete", "Le nouveau concessionnaire fait des ravages"}, "RUDL",{}, 0)), \
                     (NPC("texture/texture_npc/npcpkmn.png", 1, 8, {"Salut2", "pioupiou", "hello!", "okok"},"RRUUUDDDLL",{},0))}, \
                     {Obstacle("texture/texture_obstacle/garage_tile.png", 8, 1, sf::Vector2u(10,7),2, 3)}, \
                    "sound/music/music1.ogg")

#define MAP4 Map({  {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,10,10,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },\
                    {1 ,1 ,4 ,1 ,16,4 ,4 ,4 ,4 ,1 ,16,4 ,4 ,4 ,4 ,4 ,4 ,12,1 ,16,4 ,4 ,4 ,16,1 ,12,4 ,4 ,4 ,1 ,1 },\
                    {1 ,16,10,1 ,0 ,0 ,1 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,18,10,10,0 ,1 ,0 ,0 ,1 ,10,0 ,1 ,12,16,1 },\
                    {1 ,2 ,0 ,1 ,0 ,12,1 ,0 ,12,12,0 ,12,1 ,12,10,18,1 ,1 ,1 ,0 ,16,1 ,16,0 ,0 ,10,16,1 ,0 ,6 ,1 },\
                    {1 ,2 ,0 ,1 ,1 ,1 ,1 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,16,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,6 ,1 },\
                    {1 ,16,12,0 ,0 ,18,1 ,0 ,10,1 ,16,0 ,12,0 ,12,0 ,0 ,0 ,1 ,16,0 ,12,10,18,0 ,0 ,16,1 ,16,6 ,1 },\
                    {1 ,2 ,0 ,1 ,0 ,0 ,1 ,0 ,12,1 ,1 ,1 ,1 ,10,0 ,1 ,0 ,0 ,1 ,10,0 ,1 ,0 ,16,1 ,1 ,1 ,1 ,0 ,18,1 },\
                    {1 ,2 ,16,1 ,12,14,1 ,14,12,1 ,16,10,12,0 ,12,1 ,0 ,0 ,12,0 ,16,1 ,10,10,1 ,16,12,10,0 ,16,1 },\
                    {1 ,2 ,12,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,16,0 ,1 ,1 ,1 ,1 ,0 ,1 ,1 },\
                    {1 ,2 ,0 ,1 ,16,12,0 ,0 ,18,1 ,0 ,0 ,1 ,0 ,10,0 ,12,0 ,0 ,10,12,1 ,10,0 ,0 ,12,10,0 ,12,6 ,1 },\
                    {1 ,16,0 ,1 ,12,0 ,1 ,1 ,1 ,1 ,0 ,0 ,1 ,0 ,10,16,0 ,10,1 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,6 ,1 },\
                    {1 ,2 ,0 ,0 ,0 ,0 ,12,0 ,0 ,1 ,0 ,12,0 ,0 ,12,0 ,12,10,0 ,10,0 ,0 ,0 ,18,1 ,0 ,0 ,10,10,6 ,1 },\
                    {1 ,2 ,16,1 ,0 ,16,1 ,16,0 ,1 ,1 ,1 ,1 ,16,10,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,16,1 ,10,0 ,1 ,1 ,1 ,1 },\
                    {1 ,2 ,0 ,1 ,10,0 ,1 ,10,0 ,0 ,0 ,10,10,0 ,0 ,10,12,10,1 ,12,0 ,10,10,0 ,1 ,0 ,10,1 ,12,16,1 },\
                    {1 ,2 ,1 ,1 ,16,0 ,1 ,0 ,16,1 ,1 ,1 ,1 ,0 ,0 ,1 ,10,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,1 ,10,6 ,1 },\
                    {1 ,2 ,0 ,10,0 ,0 ,1 ,10,18,0 ,10,0 ,1 ,0 ,0 ,1 ,10,0 ,0 ,10,14,1 ,16,18,0 ,0 ,10,0 ,10,6 ,1 },\
                    {1 ,16,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,12,1 ,1 ,1 ,1 ,10,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,6 ,1 },\
                    {1 ,18,10,12,0 ,10,0 ,0 ,12,1 ,10,0 ,12,10,10,0 ,0 ,12,1 ,14,0 ,10,0 ,12,0 ,12,10,12,0 ,6 ,1 },\
                    {1 ,1 ,1 ,1 ,0 ,16,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,18,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,16,1 ,10,16,1 ,0 ,6 ,1 },\
                    {1 ,1 ,16,8 ,8 ,1 ,16,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,1 ,8 ,8 ,8 ,8 ,18,1 ,16,1 ,1 },\
                    {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 }},\
                    "sound/music/music1.ogg")

#define MAP5 MapIndoors("GARE", \
                        "texture/texture_decor/decorgare.jpg", \
                        {(NPC("texture/texture_npc/npc.png", 10, 1, {"Voulez vous manger avec moi?", "QUOI, COMMENT CA NON", "CETAIT UNE PIZZA AU CACA"},"RUUULRRDULLRDDDL",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 16, 15, 0))}, \
                        "sound/music/music2.ogg",4,150)

#define MAP6 MapIndoors("ROOM", \
                        "texture/texture_decor/room.png", \
                        {(NPC("texture/texture_npc/door_invisible.png", 80, 400, {"BAGARRE"},"",{},1)),\
                         (NPC("texture/texture_npc/door_invisible.png", 500, 320, {"EXITROOM"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 10, 5, 0)), \
                        (Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 5, 0))}, \
                        "sound/music/music2.ogg",1,150)

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
                        (NPC("texture/texture_npc/door_invisible.png", 565, 700, {"BOTTES","Quelqu'un semble tourner une video derriere" , "Salut a tous c'est Skyyart, aujourd'hui\n toute nouvelle video", "En fait si tu ignite on CD, avec les degats du Luden", "Si tu rajoutes a ca le dernier buff des mages", "Normalement tu peux one shot Cait puis\npush la lane into Nashor","... Il vous apercoit ...", "EH TOI LA REND MOI MES BOTTES"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 840, 700, {"CUISINE"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 15, 12, 0)), \
                        (Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 2, 0))}, \
                        "sound/music/music2.ogg",3,250)
                        

#define MAP8 MapIndoors("KITCHEN", \
                        "texture/texture_decor/kitchen.jpg", \
                        {(NPC("texture/texture_obstacle/key.png", 188, 200, {"KEY", "Wow there's keys !!", "Probably one student forgot them there", "Oh, there is something written on it?", "'with great power comes great responsibility'"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 5, 3, 0))}, \
                        "sound/music/music1.ogg",1,100)

#define MAP9 MapIndoors("AIRPORT", \
                        "texture/texture_decor/aeroport.jpg", \
                        {(NPC("texture/texture_npc/npc_airport.png", 326, 143, {"Salut!", "Tu viens d'arriver?", "QUESTION"}, "", \
                        {Answer("Oui, pk",{"Je dois te prevenir, les taxis sont en greve", "tu vas devoir prendre les transports","Ou bien il y a une agence de location de vehicule qui a ouvert\nTu peux tenter ta chance elle n'est pas loin",  "Il faut que tu prennes a droite, si c'est ferme tu vas\n devoir faire un detour par le haut!"},0), \
                        Answer("non tkt",{"Ah alors tu dois deja savoir ce qu'il se passe\nBon courage!"},1),Answer("maybe",{"Comment ca maybe, pk tu fais le ricain ici?"},2)},1)), \
                        (NPC("texture/texture_npc/valise.png", 476, 170, {"ENIGME1"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 3, 0))}, \
                        "sound/music/music1.ogg",1,180)
                        
#define MAP10 MapIndoors("CONCESS", \
                        "texture/texture_decor/concess_indoors.png", \
                        {(NPC("texture/texture_obstacle/key.png", 188, 200, {"KEY", "Wow there's keys !!", "Probably one student forgot them there", "Oh, there is something written on it?", "'with great power comes great responsibility'"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 5, 3, 0))}, \
                        "sound/music/music1.ogg",1,100)


