#ifndef MAP_H
#define MAP_H

struct Tile {
    bool canWalk;
    bool isExplored;
    int ch;
    Tile() : canWalk(false), isExplored(false), ch('#'){}
};

class Map {
    public:
        int width, height;
        bool post_gen;
        Map(int width, int height);
        ~Map();
        bool isWall(int x, int y) const;
        bool canWalk(int x, int y) const;
        int getChar(int x, int y) const;
        void render(TCOD_Console *con) const;
        void test_dig(int x1, int y1, int x2, int y2);
        bool isInFOV(int x, int y) const;
        void computeFOV();
        bool isExplored(int x, int y) const;
    protected:
        Tile *tiles;
        TCODMap *map;
        friend class BSPListener;

        void addMonster(int x, int y);
        void setWall(int x, int y);
        void dig(int x1, int y1, int x2, int y2);
        void createRoom(bool first, int x1, int y1, int x2, int y2);
};

#endif