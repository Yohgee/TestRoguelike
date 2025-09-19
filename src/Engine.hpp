#ifndef ENGINE_H
#define ENGINE_H

#include "Map.hpp"
#include "Gui.hpp"

class Engine {
    public:
        enum GameStatus{
            STARTUP,
            IDLE,
            NEW_TURN,
            VICTORY,
            DEFEAT
        } gameStatus;
        TCODList<Actor *> actors;
        Actor *player;
        Map *map;
        int fovRadius;
        int mapWidth;
        int mapHeight;
        int guiBarHeight;
        int guiBarWidth;
        TCOD_key_t lastKey;
        Engine(int mapWidth, int mapHeight, int guiBarWidth, int guiBarHeight);
        ~Engine();
        Gui *gui;
        void update();
        void render(TCOD_Console *con);
        void sendToBack(Actor * actor);
        
    private:
        bool computeFOV;
};

extern Engine engine;

#endif