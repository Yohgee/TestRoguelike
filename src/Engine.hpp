#ifndef ENGINE_H
#define ENGINE_H

#include <libtcod.hpp>
#include "Actor.hpp"
#include "Map.hpp"

class Engine {
    public:
        TCODList<Actor *> actors;
        Actor *player;
        Map *map;
        Engine();
        ~Engine();
        void update();
        void render(TCOD_Console *con);
};


#endif