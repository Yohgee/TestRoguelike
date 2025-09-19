#include <libtcod.hpp>
#include "main.hpp"

static const int MAX_ROOM_SIZE = 12;
static const int MIN_ROOM_SIZE = 4;

class BSPListener : public ITCODBspCallback {
    private :
        Map &map;
        int roomNum;
        int lastx,lasty;
    public :
        BSPListener(Map &map) : map(map), roomNum(0){}
        bool visitNode(TCODBsp *node, void *userData) {
            if (node->isLeaf()){
                int x,y,w,h;

                TCOD_Random *rng = TCOD_random_get_instance();
                w = TCOD_random_get_int(rng, MIN_ROOM_SIZE, node->w-2);
                h = TCOD_random_get_int(rng, MIN_ROOM_SIZE, node->h-2);
                x = TCOD_random_get_int(rng, node->x + 1, node->x + node->w - w - 1);
                y = TCOD_random_get_int(rng, node->y + 1, node->y + node->h - h - 1);
                map.createRoom(roomNum == 0, x, y, x+w - 1, y+h-1);

                if (roomNum != 0){
                    map.dig(lastx, lasty, x + w/2, lasty);
                    map.dig(x + w/2, lasty, x + w/2, y + h/2);
                }

                lastx = x + w/2;
                lasty = y + h/2;
                roomNum++;
            }

            return true;
        }
};

Map::Map(int width, int height) : width(width), height(height){
    tiles = new Tile[width * height];
    map = new TCODMap(width, height);
    post_gen = false;
    //setWall(20,20);

    TCODBsp bsp(0,0, width, height);
    bsp.splitRecursive(NULL, 8, MAX_ROOM_SIZE, MAX_ROOM_SIZE, 1.5f, 1.5f);
    BSPListener listener(*this);
    bsp.traverseInvertedLevelOrder(&listener, NULL);

    computeFOV();
    post_gen = true;
}

Map::~Map(){
    delete [] tiles;
    delete map;
}

bool Map::isWall(int x, int y) const{
    return !map->isWalkable(x, y);
}

bool Map::canWalk(int x, int y) const {
    if (isWall(x, y)){
        return false;
    }

    for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++){
        Actor * actor = *iterator;
        if (actor->blocks && actor->x == x && actor->y == y){
            return false;
        }
    }

    return true;
}

bool Map::isExplored(int x, int y) const{
    return tiles[x + y * width].isExplored;
}

bool Map::isInFOV(int x, int y) const{
    if (map->isInFov(x, y)){
        tiles[x + y * width].isExplored = true;
        return true;
    }
    return false;
}

void Map::computeFOV(){
    map->computeFov(engine.player->x, engine.player->y, engine.fovRadius);
}

void Map::setWall(int x, int y){
    tiles[x + y*width].canWalk = false;
}

int Map::getChar(int x, int y) const{
    return tiles[x + y * width].ch;
}

void Map::addMonster(int x, int y){
        float f = TCOD_random_get_float(NULL, 0, 1);
        if (f < 0.8f){
            Actor * a = new Actor(x, y, 'o', "orc", TCOD_dark_green);
            a->destructible = new Destructible(10, 1, "orc corpse");
            a->attacker = new Attacker(3, 0);
            a->ai = new MonsterAi();
            engine.actors.push(a);
            printf("test x: %d, y: %d\n", x, y);
        } else {
            Actor * a = new Actor(x, y, 'T', "troll", TCOD_dark_green);
            a->destructible = new Destructible(15, 2, "troll corpse");
            a->attacker = new Attacker(5, 0);
            a->ai = new MonsterAi();
            engine.actors.push(a);
        }
}

void Map::dig(int x1, int y1, int x2, int y2){
    if (x2 < x1){
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
    }

    if (y2 < y1){
        int tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    for (int x = x1; x <= x2; x++){
        for (int y = y1; y <= y2; y++){
            map->setProperties(x, y, true, true);
            if (post_gen){
                tiles[x + y*width].ch = '.';
            } else {
                tiles[x + y*width].ch = ' ';
            }
        }
    }
}

void Map::test_dig(int x1, int y1, int x2, int y2){
    dig(x1,y1,x2,y2);
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2){
    dig(x1,y1,x2,y2);
    if (first){
        engine.player->x = (x1+x2)/2;
        engine.player->y = (y1+y2)/2;
    } else {
        TCOD_Random *rng = TCOD_random_get_instance();
        int n = TCOD_random_get_int(rng, 0, 3);
        for (int i = 0; i < n; i++){
            addMonster(TCOD_random_get_int(NULL, x1, x2), TCOD_random_get_int(NULL, y1,y2));
        }
    }
}

void Map::render(TCOD_Console *con) const{
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            if (isInFOV(x, y)){
                TCOD_console_put_char_ex(con, x, y, getChar(x, y), TCOD_dark_gray, TCOD_black);
            } else if (isExplored(x, y)){
                TCOD_console_put_char_ex(con, x, y, getChar(x, y), TCOD_dark_gray, TCOD_black);
            }
            TCOD_console_put_char_ex(con, x, y, getChar(x, y), TCOD_dark_gray, TCOD_black);
        }
    }
}