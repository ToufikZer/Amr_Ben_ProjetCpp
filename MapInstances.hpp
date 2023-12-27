#pragma once

#include "iostream"
#include "Map.hpp"
#include "MapIndoors.hpp"
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
                    {(NPC("texture/texture_npc/npcpkmn.png", 8, 13, {"Salut", "test", "caca"},"RULD")), \
                     (NPC("texture/texture_npc/npcpkmn.png", 1, 8, {"Salut2", "pioupiou", "hello!"},"RUUUDDDLL"))}, \
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
                    {(NPC("texture/texture_npc/npcpkmn.png", 9, 9, {"Salut", "test", "caca"},"UUUUDDDD")), \
                     (NPC("texture/texture_npc/npcpkmn.png", 0, 3, {"Salut2", "pioupiou", "hello!"},"RULD"))}, \
                    {Obstacle("texture/texture_obstacle/Crous.png", 9, 1, sf::Vector2u(10,7), sf::Vector2u(12,7),2, 1)}, \
                    "sound/music/music2.ogg")



#define MAP3 Map({{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},\
                    {1,2,2,2,2,2,2,0,0,0,0,2,0,0,0,1},\
                    {1,2,0,0,0,0,0,0,3,3,3,3,3,3,3,1},\
                    {1,2,0,0,1,3,3,3,3,0,1,1,1,0,0,1},\
                    {1,2,2,0,3,3,3,0,0,0,2,1,1,1,0,1},\
                    {1,0,1,0,3,0,1,1,0,0,2,2,1,1,1,1},\
                    {1,0,2,0,3,0,1,1,1,0,1,2,1,1,1,1},\
                    {1,0,2,0,3,2,1,1,0,0,0,0,1,1,2,0},\
                    {1,0,0,0,0,0,2,1,1,1,1,1,1,1,0,0},\
                    {1,1,1,1,1,0,2,0,0,0,0,0,0,0,0,1},\
                    {1,2,0,0,0,0,0,0,3,0,3,3,3,3,3,1},\
                    {1,1,0,0,1,0,3,3,3,0,1,1,2,0,0,1},\
                    {1,2,2,0,3,3,3,0,0,0,2,1,1,1,0,1},\
                    {1,0,1,0,3,0,1,2,0,0,2,2,2,1,1,1},\
                    {1,0,0,0,3,0,2,2,2,0,2,1,1,1,1,1},\
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 8, 13, {"Voulez vous manger avec moi?", "QUOI, COMMENT CA NON", "CETAIT UNE PIZZA AU CACA"},"RUUULRRDULLRDDDL")), \
                     (NPC("texture/texture_npc/npcpkmn.png", 1, 8, {"Salut2", "pioupiou", "hello!"},"RRUUUDDDLL"))}, \
                    "sound/music/music1.ogg")

#define MAP4 Map({{3,3,3,3,3,3,3},\
                    {3,0,0,0,0,0,3},\
                    {3,0,0,0,0,0,3},\
                    {3,0,0,0,0,0,3},\
                    {3,0,0,0,0,0,3},\
                    {3,0,0,0,0,0,3},\
                    {3,3,3,0,3,3,3}}, \
                    {(NPC("texture/texture_npc/npcpkmn.png", 5, 5, {"Voulez vous manger avec moi?", "QUOI, COMMENT CA NON", "CETAIT UNE PIZZA AU CACA"},"RUUULRRDULLRDDDL"))}, \
                    {Obstacle("texture/texture_obstacle/door.png", 3, 6, sf::Vector2u(3,5),3, 2)}, \
                    "sound/music/music1.ogg")

#define MAP5 MapIndoors("GARE", \
                        "texture/texture_decor/decorgare.jpg", \
                        {(NPC("texture/texture_npc/npc.png", 10, 1, {"Voulez vous manger avec moi?", "QUOI, COMMENT CA NON", "CETAIT UNE PIZZA AU CACA"},"RUUULRRDULLRDDDL"))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 16, 15, 0))}, \
                        "sound/music/music2.ogg",4)

#define MAP6 MapIndoors("MARIO", \
                        "texture/texture_decor/mario.png", \
                        "sound/music/music2.ogg",1)

#define MAP7 MapIndoors("CROUS", \
                        "texture/texture_decor/crous.png", \
                        {(NPC("texture/texture_npc/door_invisible.png", 20, 4, {"Voulez vous manger avec moi?"},"")), \
                        (NPC("texture/texture_npc/door_invisible.png", 28, 4, {"Voulez vous manger avec moi?"},"")), \
                        (NPC("texture/texture_npc/door_invisible.png", 39, 4, {"Voulez vous manger avec moi?"},"")), \
                        (NPC("texture/texture_npc/door_invisible.png", 5, 16, {"Voulez vous manger avec moi?"},"")), \
                        (NPC("texture/texture_npc/door_invisible.png", 18, 16, {"Voulez vous manger avec moi?"},"")), \
                        (NPC("texture/texture_npc/door_invisible.png", 23, 16, {"Voulez vous manger avec moi?"},"")), \
                        (NPC("texture/texture_npc/door_invisible.png", 39, 16, {"Voulez vous manger avec moi?"},"")), \
                        (NPC("texture/texture_npc/door_invisible.png", 60, 8, {"Voulez vous manger avec moi?"},"")), \
                        (NPC("texture/texture_npc/door_invisible.png", 60, 8, {"Voulez vous manger avec moi?"},"")), \
                        (NPC("texture/texture_npc/door_invisible.png", 60, 8, {"Voulez vous manger avec moi?"},""))}, \
                        {(Obstacle("texture/texture_obstacle/invisible_wall.png", 16, 12, 0))}, \
                        "sound/music/music2.ogg",3)
                        
                        

