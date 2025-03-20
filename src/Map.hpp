#ifndef MAP_H
#define MAP_H

#include <libtcod.hpp>

struct Tile {
    bool canWalk;
    Tile() : canWalk(true){}
};

class Map {
    public:
        int width, height;

        Map(int width, int height);
        ~Map();
        bool isWall(int x, int y) const;
        void render(TCOD_Console *con) const;
    protected:
        Tile *tiles;

        void setWall(int x, int y);
};

#endif