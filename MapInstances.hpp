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
                    {1,3,3,3,3,0,0,0,3,3,3,2,2,2,2,1},\
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
                     {Obstacle("texture/texture_obstacle/gare.png", 1, 1, sf::Vector2u(6,7),2, 5)}, \
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
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},\
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

#define MAP_S Map({{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,2,2,2,2,2,2,2,1},\
                    {1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,1},\
                    {1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,1},\
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 5, 7, {"Y'a beaucoup de touriste ces temps ci,\nc'est a en perdre la tete", "Le nouveau concessionnaire fait des ravages"}, "RUDL",{}, 0)), \
                     (NPC("texture/texture_npc/npcpkmn.png", 1, 8, {"Salut2", "pioupiou", "hello!", "okok"},"RRUUUDDDLL",{},0))}, \
                     {Obstacle("texture/texture_obstacle/stade.png", 7, 9, sf::Vector2u(6,11), sf::Vector2u(6,12),0, 6)}, \
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
                        {(NPC("texture/texture_npc/door_invisible.png", 20, 40, {"EXITGARE"},"",{},1)), \
                        (NPC("texture/texture_npc/npc_invisible.png", 848, 906, {"Voulez vous frauder?","QUESTION"},"",{Answer("Oui!",{"Fraudons!"},0),Answer("NON!",{"Avez vous assez d'argent?"},1)},1)), \
                        (NPC("texture/texture_npc/sdf1.png", 463, 100, {"La gestion du pays devient catastrophique,", "Annie d'Algo et Valery PekinExpress\nont passe le ticket de metro a 4 euros.", "Rien ne va plus, en plus, avec ce froid\ndehors les sdf n'ont pas le choix,", "Ils doivent se refugier dans cette gare.", "Heureusement ils sont tres genereux,peut\netre qu'en resolvant leur enigme", "Ils accepteront de te donner une\npetite compensation.","Quitte a ne pas avoir de morale pour voler\ntu peux aussi frauder, a tes risques et perils!"},"",{},1)),\
                        (NPC("texture/texture_npc/sdf2.png", 222, 344, {"ENIGME1"},"",{},1)), \
                        (NPC("texture/texture_npc/sdf3.png", 294, 642, {"ENIGME2"},"",{},1)), \
                        (NPC("texture/texture_npc/npc2.png", 809, 591, {"ENIGME3"},"",{},1)), \
                        (NPC("texture/texture_npc/sdf1.png", 789, 821, {"Tu veux parler avec moi?","QUESTION"},"",{Answer("Oui!",{"Flemme en fait"},0),Answer("NON!",{"PARLE AVEC MOI"},1)},1)), \
                        (NPC("texture/texture_npc/sdf4.png", 315, 881, {"ENIGME4"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 16, 15, 0)), \
                        (Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 2, 0))}, \
                        "sound/music/music2.ogg",4,230)

#define MAP6 MapIndoors("ROOM", \
                        "texture/texture_decor/room.png", \
                        {(NPC("texture/texture_npc/npc_invisible.png", 80, 400, {"Mais qu'est ce que tu fais chez moi\nSORS DE LA!!!","BATS TOI"},"",{},1)),\
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
                        (NPC("texture/texture_npc/valise.png", 476, 170, {{"KNIFE","Oh un couteau...", "Ca pourrait etre utile"}},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 3, 0))}, \
                        "sound/music/music1.ogg",1,180)
                        
#define MAP10 MapIndoors("CONCESS", \
                        "texture/texture_decor/concess_indoors.png", \
                        {(NPC("texture/texture_npc/npc_invisible.png", 240, 200, {"Salut", "Tu viens pour louer une voiture?", "Je suis desole,tous les modeles abordables\nviennent de partir comme des petits pains!","Il me reste que des modeles probablement\nhors de prix pour toi desole","Tu as beaucoup d'argent?", "QUESTION"},"",{Answer("300 euros",{"Bon il reste toujours ce modele de golmon","Raboule ton argent et interagis avec lui"},0),Answer("Pas un rond",{"Pourquoi tu me parles alors?", "Vas-y a pied si c'est comme ca!"},1),Answer("Je suis RICHE",{"Oui oui et moi je suis developpeur de jeu \nvideo tant que tu y es", "Allez va-t-en!"},2)},1)), \
                        (NPC("texture/texture_obstacle/invisible_wall.png", 0, 200,{"EXITCONCESS"},"",{},1)), \
                        (NPC("texture/texture_npc/door_invisible.png", 30, 200,{"CAR"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 4, 0)), \
                        (Obstacle("texture/texture_obstacle/invisible_wall.png", 5, 4, 0))}, \
                        "sound/music/music1.ogg",1,100)

#define MAP11 MapIndoors("STADE", \
                        "texture/texture_decor/stade_in.png", \
                        {(NPC("texture/texture_npc/sdf2.png", 40, 100,{"ANNIE, A CAUSE DE TOI MA JOURNEE\nA ETE UN CAUCHEMAR", "J'AI DU FRAPPER UN ETUDIANT\nVOLER, FRAUDER", "ET EN PLUS, J'AI RATE LE MATCH\nPOUR LEQUEL JE SUIS VENU", "EH C'EST QUOI CETTE POUD...", "*Vous vous evanouissez brusquement...*"},"",{},1)), \
                        (NPC("texture/texture_npc/sdf1.png", 200, 100,{"Tu viens seulement d'arriver?", "Tu etais pour qui?", "QUESTION"},"",{Answer("L'algerie !", {"Tu viens de louper le match du siecle", "L'algerie a gagne 13-2\n*Tous ca a cause de Annie d'Algo*"}, 0), Answer("PAS l'Algerie", {"Eh bah, t'es pas chanceux mon pote...", "Ton equipe vient de perdre 2-13\nEt en plus t'as rien vu", "*Tout ca a cause de Annie d'Algo*"}, 1)},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 3, 0)), \
                        (Obstacle("texture/texture_obstacle/invisible_wall.png", 5, 3, 0))}, \
                        "sound/music/music1.ogg",1,100)

#define MAP12 MapIndoors("FINAL", \
                        "texture/texture_decor/final.png", \
                        {(NPC("texture/texture_npc/npc_invisible.png", 160, 150,{"PREPARE TOI, C'EST LA BATAILLE FINALE\n DERESHISHISHISHISHI!", "AFFRONTE MOI"},"",{},1))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 0, 3, 0)), \
                        (Obstacle("texture/texture_obstacle/invisible_wall.png", 6, 3, 0))}, \
                        "sound/music/music1.ogg",1,100)


