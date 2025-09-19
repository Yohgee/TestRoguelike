#ifndef AI_H
#define AI_H

class Ai {
    public:
        virtual void update(Actor * owner) = 0;
};

class PlayerAi : public Ai {
    public:
        void update(Actor * owner);
    protected:
        bool moveOrAttack(Actor * owner, int tx, int ty);
};

class MonsterAi : public Ai {
    public:
        void update(Actor * owner);
    protected:
        int moveCount;
        static const int TRACKING_TURNS = 3;
        void moveOrAttack(Actor * owner, int tx, int ty);
};

#endif