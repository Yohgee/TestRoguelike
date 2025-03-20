#include <libtcod.hpp>
#include "Map.hpp"

Map::Map(int width, int height) : width(width), height(height){
    tiles = new Tile[width * height];

    setWall(20,20);
}

Map::~Map(){
    delete [] tiles;
}

bool Map::isWall(int x, int y) const{
    return !tiles[x + y*width].canWalk;
}

void Map::setWall(int x, int y){
    tiles[x + y*width].canWalk = false;
}

void Map::render(TCOD_Console *con) const{
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            TCOD_console_put_char_ex(con, x, y, isWall(x,y) ? '#' : ' ', TCOD_amber, TCOD_black);
        }
    }
}