#include <libtcod.hpp>
#include "main.hpp"

void PlayerAi::update(Actor * owner){
    if (owner->destructible && owner->destructible->isDead()){
        return;
    }

    int dx = 0, dy = 0;

    TCOD_key_t key = engine.lastKey;

    switch (key.vk){
        case TCODK_UP:
            dy = -1;
        break;
        case TCODK_DOWN:
            dy = 1;
        break;
        case TCODK_LEFT:
            dx = -1;
        break;
        case TCODK_RIGHT:
            dx = 1;
        break;
        case TCODK_TEXT:
            std::printf(key.text);
            switch (key.text[0]){
                case 'd':
                    engine.map->test_dig(owner->x-3, owner->y-3, owner->x + 3, owner->y + 3);
                break;
                case 'e':
                    for (Actor ** i = engine.actors.begin(); i != engine.actors.end(); i++) {
                        Actor * a = *i;
                        if (a->devourable && a != owner && a->x == owner->x && a->y == owner->y){
                            a->devourable->devour(a, owner);
                        }
                    }
                break;
                default : break;
            }
        break;
        default: break;
    }
    if (dx != 0 || dy != 0){
        engine.gameStatus = Engine::NEW_TURN;
        if (moveOrAttack(owner, owner->x + dx, owner->y + dy)){
            engine.map->computeFOV();
        }
    }
}

bool PlayerAi::moveOrAttack(Actor * owner, int tx, int ty){
    if (engine.map->isWall(tx, ty)) {
        return false;
    }

    for (Actor **i = engine.actors.begin(); i != engine.actors.end(); i++){
        Actor *actor = *i;
        if (actor->destructible && !actor->destructible->isDead() && actor->x == tx && actor->y == ty){
            owner->attacker->attack(owner, actor);
            return false;
        }

        if (actor->destructible && actor->destructible->isDead() && actor->x == tx && actor->y == ty){
            engine.gui->message(TCOD_ColorRGB{127,127,127}, "There is a %s lying on the floor.\0", actor->name);
        }
    }

    owner->x = tx;
    owner->y = ty;
    return true;
}

void MonsterAi::update(Actor * owner){
    if (owner->destructible && owner->destructible->isDead()){
        return;
    }

    if (engine.map->isInFOV(owner->x, owner->y)){
        moveCount = TRACKING_TURNS;
    } else if (moveCount >= 0){
        moveCount--;
    }
    if (moveCount > 0){
        moveOrAttack(owner, engine.player->x, engine.player->y);
    }
}

void MonsterAi::moveOrAttack(Actor * owner, int tx, int ty){
    int dx = tx - owner->x;
    int dy = ty - owner->y;
    int stepdx = (dx > 0 ? 1 : -1);
    int stepdy = (dy > 0 ? 1 : -1);
    float d = sqrtf(dx * dx + dy * dy);
    if (d >= 2){
        dx = (int)round(dx/d);
        dy = (int)round(dy/d);

        if (engine.map->canWalk(owner->x + dx, owner->y + dy)){
            owner->x = owner->x + dx;
            owner->y = owner->y + dy;
        } else if (engine.map->canWalk(owner->x + stepdx, owner->y)){
            owner->x += stepdx;
        } else if (engine.map->canWalk(owner->x, owner->y + stepdy)){
            owner->y += stepdy;
        }
    } else if (owner->attacker) {
        owner->attacker->attack(owner, engine.player);
    }
    
}