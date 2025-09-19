#include "main.hpp"

Devourable::Devourable(float sat){
    saturation = sat;
}

void Devourable::devour(Actor * owner, Actor * devourer){
    if (devourer->destructible){
        devourer->destructible->hp += saturation;
        if (devourer->destructible->hp > devourer->destructible->maxHP){
            devourer->destructible->hp = devourer->destructible->maxHP;
        }
    }

    engine.gui->message(TCOD_ColorRGB{191,0,0}, "You devour the %s, and regain %g hit points.\0", owner->name, saturation);

    engine.actors.remove(owner);

}