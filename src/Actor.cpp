#include <libtcod.hpp>
#include "main.hpp"

Actor::Actor(int x, int y, int ch, const char *name, const TCOD_color_t &col) :
    x(x),y(y), ch(ch), name(name), col(col), attacker(NULL), destructible(NULL), ai(NULL), devourable(NULL), blocks(true) {

}

void Actor::render(TCOD_Console *console) const{
    TCOD_console_put_char_ex(console, x, y, ch, col, TCOD_ColorRGB{0, 0, 0});
}

void Actor::update(){
    printf("uh");
}

bool Actor::moveOrAttack(int nx, int ny){
    if (engine.map->isWall(nx, ny)) {
        return false;
    }

    for (Actor **i = engine.actors.begin(); i != engine.actors.end(); i++){
        Actor *actor = *i;
        if (actor->blocks && actor->x == nx && actor->y == ny){
            printf("You attack the %s", actor->name);
            return false;
        }
    }
    this->x = nx;
    this->y = ny;
    return true;
}