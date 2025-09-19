#include <libtcod.hpp>
#include "main.hpp"

Attacker::Attacker(float damage, float pierce) : damage(damage), pierce(pierce) {

}

void Attacker::attack(Actor * owner, Actor * target){
    if (!target->destructible || target->destructible->isDead()){
        engine.gui->message(TCOD_ColorRGB{255,255,255}, "%s tries to attack the unattackble %s.\0", owner->name, target->name);
        return;
    }
    float hit_dmg = damage - target->destructible->def;
    if (hit_dmg > 0){
        engine.gui->message(TCOD_ColorRGB{255,63,63}, "%s attacks %s for %g damage.\0", owner->name, target->name, hit_dmg);
    } else {
        engine.gui->message(TCOD_ColorRGB{255,255,255}, "%s misses %s.\0", owner->name, target->name);
    }
    target->destructible->takeDamage(target, damage);


}