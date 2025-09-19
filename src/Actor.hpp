#ifndef ACT_H
#define ACT_H

#include "Attacker.hpp"
#include "Destructible.hpp"
#include "Ai.hpp"
#include "Devourable.hpp"


class Actor {
    public: 
        int x,y;
        int ch;
        const char * name;
        bool blocks;
        Attacker * attacker;
        Destructible * destructible;
        Ai * ai;
        Devourable * devourable;
        TCOD_color_t col;
        Actor(int x, int y, int ch, const char *name, const TCOD_color_t &col);
        //~Actor();
        void render(TCOD_Console *console) const;
        void update();
        bool moveOrAttack(int x, int y);
};

#endif