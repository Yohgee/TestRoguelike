#include <libtcod.hpp>
#include "Actor.hpp"

Actor::Actor(int x, int y, int ch, const TCOD_color_t &col) :
    x(x),y(y), ch(ch), col(col) {

}

void Actor::render(TCOD_Console *console) const{
    TCOD_console_put_char_ex(console, x, y, ch, col, TCOD_black);
}