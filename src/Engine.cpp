#include <libtcod.hpp>
#include <SDL.h>
#include "main.hpp"

Engine::Engine(int mapWidth_, int mapHeight_, int guiBarWidth_, int guiBarHeight_) : gameStatus(STARTUP){
    mapWidth = mapWidth_;
    mapHeight = mapHeight_;
    guiBarWidth = guiBarWidth_;
    guiBarHeight = guiBarHeight_;
    
    player = new Actor(4, 4, '@', "player", TCOD_ColorRGB{255,255,255});
    player->destructible = new Destructible(30, 2, "your corpse");
    player->ai = new PlayerAi();
    player->attacker = new Attacker(5, 2);
    actors.push(player);
    computeFOV = false;
    fovRadius = 10;
    gui = new Gui();
    map = new Map(mapWidth,mapHeight);
}

Engine::~Engine(){
    actors.clearAndDelete();
    delete map;
    delete gui;
}

void Engine::update(){
    if (gameStatus == STARTUP){
        map->computeFOV();
    }
    gameStatus = IDLE;
    SDL_Event sdl_event;
    TCOD_key_t key;
    while(SDL_PollEvent(&sdl_event)){
        TCOD_event_t event = tcod::sdl2::process_event(sdl_event, key);

        if (event == TCOD_EVENT_NONE || event == TCOD_EVENT_KEY_RELEASE){
            return;
        }
        
        lastKey = key;

        player->ai->update(player);

        if (gameStatus == NEW_TURN){
            for (Actor **i = actors.begin(); i != actors.end(); i++){
                Actor * a = *i;
                if (a != player){
                    a->ai->update(a);
                }
            }
            gameStatus = IDLE;
        }
    }

    if (computeFOV){
        map->computeFOV();
        computeFOV = false;
    }

}

void Engine::sendToBack(Actor * actor){
    actors.remove(actor);
    actors.insertBefore(actor, 0);
}

void Engine::render(TCOD_Console *con){

    tcod::Console map_con = tcod::Console{mapWidth, mapHeight};

    map->render(map_con.get());

    for (Actor **a = actors.begin(); a != actors.end(); a++){
        Actor *actor = *a;
        if (map->isInFOV(actor->x, actor->y)){
            actor->render(con);
        }
        actor->render(map_con.get());
    }

    //redraw player for layering
    player->render(map_con.get());

    gui->render(con);

    tcod::blit(*con, *map_con.get(), {0,0}, {0, -Gui::PANEL_HEIGHT, mapWidth, mapHeight + Gui::PANEL_HEIGHT});
    //TCOD_console_printf(con, 1, 1, "HP: %d/%d", (int) player->destructible->hp, (int) player->destructible->maxHP);
    //TCOD_console_printf(con, 1, 2, "X: %d, Y: %d", (int) player->x, (int) player->y);
}