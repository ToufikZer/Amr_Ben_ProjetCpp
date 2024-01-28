#include "iostream"
#include "MapManager.hpp"
#include <SFML/Audio.hpp>
#include "MapInstances.hpp"

Map map1 = MAP1;
Map map2 = MAP2;
Map map3 = MAP3;
Map map0 = MAP0;
MapManager::MapManager(){
    MapMap = {{map0, map3, map1, map2}}; 
}
