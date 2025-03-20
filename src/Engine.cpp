#include <libtcod.hpp>
#include <SDL.h>
#include "Engine.hpp"
#include "Actor.hpp"
#include "Map.hpp"

Engine::Engine(){
    player = new Actor(4, 4, '@', TCOD_white);
    actors.push(player);
    actors.push(new Actor(10,12,'d', TCOD_azure));

    map = new Map(80,64);
}

Engine::~Engine(){
    actors.clearAndDelete();
    delete map;
}

void Engine::update(){
    SDL_Event sdl_event;
    TCOD_key_t key;
    while(SDL_PollEvent(&sdl_event)){
        TCOD_event_t event = tcod::sdl2::process_event(sdl_event, key);
        //std::printf("key.text \"");
        //std::printf(key.text);
        //std::printf("\"\n");
        if (event == TCOD_EVENT_NONE || event == TCOD_EVENT_KEY_RELEASE){
            return;
        }
        switch (key.vk){
            case TCODK_UP:
                if (! map->isWall(player->x, player->y - 1)){
                    player->y--;
                }
            break;
            case TCODK_DOWN:
                if (! map->isWall(player->x, player->y + 1)){
                    player->y++;
                }
            break;
            case TCODK_LEFT:
                if (! map->isWall(player->x - 1, player->y)){
                    player->x--;
             }
            break;
            case TCODK_RIGHT:
                if (! map->isWall(player->x + 1, player->y)){
                    player->x++;
                }
            break;
            case TCODK_TEXT:
                std::printf(key.text);
            break;
            default: break;
        }
    }

}

void Engine::render(TCOD_Console *con){

    //TCOD_Console *console = TCOD_sys_get_internal_console();

    map->render(con);

    for (Actor **a = actors.begin(); a != actors.end(); a++){
        (*a)->render(con);
    }

    //redraw player for layering
    player->render(con);
}