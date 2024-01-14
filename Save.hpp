#pragma once

#include "GameState.hpp"
#include "Map.hpp"
#include "MapIndoors.hpp"
#include "Inventory.hpp"

class Save {
private:
    std::string StateName;
    sf::Vector2f playerPosition;
    sf::Vector2u map_coords;
    sf::Vector2u mapDimension;
    std::string MapName;
    Inventory inventaire;
    unsigned int nb_pas;
    bool game_started = false;
public:
    // Save(GameState state, Inventory inventaire)
    //     : gameState(state) {}
    Save() = default;

    Save(std::string StateName, sf::Vector2f position, sf::Vector2u map_coords,sf::Vector2u mapDimension, Inventory inventaire, bool game_started)
        : StateName(StateName), playerPosition(position), map_coords(map_coords), mapDimension(mapDimension), inventaire(inventaire), game_started(game_started) {}

    Save(std::string StateName, sf::Vector2f position, unsigned int nb_pas, sf::Vector2u mapDimension, Inventory inventaire, bool game_started)
        : StateName(StateName), playerPosition(position), nb_pas(nb_pas), mapDimension(mapDimension), inventaire(inventaire), game_started(game_started) {}

    Save(std::string StateName, sf::Vector2f position, std::string MapName, Inventory inventaire, bool game_started)
        : StateName(StateName), playerPosition(position), MapName(MapName), inventaire(inventaire), game_started(game_started) {}

    // Getters pour accéder aux attributs privés
    std::string getStateName() const {
        return StateName;
    }

    sf::Vector2f getPlayerPosition() const {
        return playerPosition;
    }

    sf::Vector2u getCurrentMap() const {
        return map_coords;
    }

    sf::Vector2u getmapDimension() const {
        return mapDimension;
    }

    std::string getName(){
        return MapName;
    }

    Inventory getInventory() const {
        return inventaire;
    }

    unsigned int getNbPas(){
        return nb_pas;
    }

    bool getGameStarted(){
        return game_started;
    }

    void setGameStarted(bool value){
        game_started = value;
    }
};