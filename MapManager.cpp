#include "iostream"
#include "MapManager.hpp"
#include <SFML/Audio.hpp>
#include "MapInstances.hpp"

Map map1 = MAP1;
Map map2 = MAP2;
Map map3 = MAP3;

MapManager::MapManager(){
    MapMap = {{map2,map3,map1},
              {map3,map1,map2}};
    current_map = sf::Vector2u(1,1); 
}



// MapManager::~MapManager() {
//     delete[] MapMap;
// }