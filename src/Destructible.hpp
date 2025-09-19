#ifndef DEST_H
#define DEST_H

class Destructible {
    public:
        float maxHP;
        float hp;
        float def;
        const char * corpseName;

        Destructible(float maxHP, float def, const char * corpseName);
        inline bool isDead() {return hp <= 0; }
        float takeDamage(Actor *owner, float damage);
        void die(Actor *owner);
};

#endif