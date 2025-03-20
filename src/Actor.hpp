#ifndef ACTOR_H
#define ACTOR_H

#include <libtcod.hpp>

class Actor {
    public: 
        int x,y;
        int ch;
        TCOD_color_t col;
        Actor(int x, int y, int ch, const TCOD_color_t &col);
        void render(TCOD_Console *console) const;
};

#endif