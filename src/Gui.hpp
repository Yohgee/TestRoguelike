#pragma once
#include "main.hpp"

class Gui {
    public:
        Gui();
        ~Gui();
        void render(TCOD_Console * dest_con);
        void message(const TCOD_color_t & col, const char * text, ...);
        static const int PANEL_HEIGHT=7;
        static const int BAR_WIDTH=20;
        static const int MSG_WIDTH=40;
        static const int MSG_HEIGHT=PANEL_HEIGHT-1;
    protected:
        tcod::Console con;
        tcod::Console msg_con;

        struct Message {
            char * text;
            TCOD_color_t col;
            Message(const char * text, const TCOD_color_t & col);
            ~Message();
        };

        TCODList<Message *> log;

        void renderBar(int x, int y, int w, const char * name, float value, float max, const TCOD_color_t &col, const TCOD_color_t & col2); 
};