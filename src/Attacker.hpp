#ifndef ATT_H
#define ATT_H

class Attacker {
    public:
        float damage;
        float pierce;
        Attacker(float damage, float pierce);
        void attack(Actor * owner, Actor * target);
};

#endif