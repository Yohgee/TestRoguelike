#include "main.hpp"

Destructible::Destructible(float maxHP, float def, const char * corpseName) : maxHP(maxHP), hp(maxHP), def(def), corpseName(corpseName){

}

void Destructible::die(Actor * owner){
    owner->ch = '%';
    owner->col = TCOD_ColorRGB{191,0,0};
    owner->name = corpseName;
    owner->blocks = false;
    owner->devourable = new Devourable(maxHP/2);
    engine.gui->message(TCOD_ColorRGB{255,0,0}, "%s has died.\0", owner->name);
}

float Destructible::takeDamage(Actor * owner, float damage){
    damage -= def;
    if (damage > 0){
        hp -= damage;
        if (hp <= 0){
            die(owner);
        }
    } else {
        damage = 0;
    }

    return damage;
}