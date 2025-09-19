#include "main.hpp"



Gui::Gui(){
    con = tcod::Console{engine.mapWidth + engine.guiBarWidth, PANEL_HEIGHT};
    msg_con = tcod::Console{MSG_WIDTH, engine.mapHeight};
}

Gui::~Gui(){
    log.clearAndDelete();
}

void Gui::render(TCOD_Console * dest_con){
    con.clear();
    msg_con.clear();
    renderBar(1, 1, BAR_WIDTH, "Health", engine.player->destructible->hp, engine.player->destructible->maxHP, TCOD_ColorRGB{0,255,0}, TCOD_ColorRGB{191,0,0});
    
    int y = 1;
    float colCoeff = 0.4f;
    for (Message ** i = log.begin(); i != log.end(); i++){
        Message * m = *i;
        //TCOD_console_set_default_foreground(con, m->col);
        //TCOD_console_print(con, MSG_X, y, m->text);
        //printf("msg: %s, x: %d, y:%d\n", m->text, MSG_X, y);
        //tcod::print(*msg_con.get(), {1, y}, m->text, TCOD_ColorRGB{(uint8_t)(255 * colCoeff), (uint8_t)(255 * colCoeff), (uint8_t)(255 * colCoeff)}, TCOD_dark_gray, TCOD_LEFT, TCOD_BKGND_NONE);
        char * c = m->text;
        int x = 0;
        while (*c != '\0'){
            if (x >= MSG_WIDTH){
                x = 0;
                y++;
            }
            TCOD_console_put_char_ex(msg_con.get(), x, y, *c, m->col, TCOD_ColorRGB{0,0,0});
            x++;
            c++;
        }
        y++;
        if ( colCoeff < 1.0f){
            colCoeff += 0.3f;
        }
    }


    tcod::blit(*dest_con, *con.get(), {0 , 0}, {0 , 0, engine.mapWidth + engine.guiBarWidth, PANEL_HEIGHT});
    tcod::blit(*dest_con, *msg_con.get(), {engine.mapWidth, 0}, {0, 0, 40, engine.mapHeight});
}

void Gui::renderBar(int x, int y, int w, const char * name, float value, float max, const TCOD_color_t & col, const TCOD_color_t & col2){
    //TCOD_console_rect(con, x, y, w, 1, false, TCOD_BKGND_SET);
    tcod::draw_rect(*con.get(), {x, y, w, 1}, 0, col2, col2, TCOD_BKGND_SET);

    int barWidth = (int)(value / max * w);
    if (barWidth > 0){
        //TCOD_console_set_default_background(con, col);
        //TCOD_console_rect(con, x, y, barWidth, 1, false, TCOD_BKGND_SET);
    tcod::draw_rect(*con.get(), {x, y, barWidth, 1}, 0, col, col, TCOD_BKGND_SET);

    }

    //TCOD_console_set_default_foreground(con, TCOD_white);
    //TCOD_console_print_ex(con, x + w/2, y, TCOD_BKGND_NONE, TCOD_CENTER, "%s: %g/%g", name, value, max);
    tcod::print(*con.get(), {x + w/2, y}, name, TCOD_ColorRGB{255,255,255}, TCOD_ColorRGB{0,0,0}, TCOD_CENTER, TCOD_BKGND_NONE);
}

void Gui::message(const TCOD_color_t & col, const char * text, ...){
    va_list ap;
    char buf[128];
    va_start(ap, text);
    vsprintf_s(buf, text, ap);
    va_end(ap);

    //char * lineBegin = buf;
    //char * lineEnd;
   // do {
        if (log.size() == MSG_HEIGHT){
            Message * toRemove = log.get(0);
            log.remove(toRemove);
            delete toRemove;
        }
        
        Message * msg = new Message(buf, col);
        log.push(msg);

        //lineEnd = strchr(lineBegin, '\n');
        //if (lineEnd){
          //  *lineEnd='\0';
       // }

        //Message * nmsg = new Message(lineBegin, col);
        //log.push(nmsg);
        //lineBegin = lineEnd + 1;
    //} while (lineEnd);
}

Gui::Message::Message(const char * text, const TCOD_color_t & col) :
text(strdup(text)), col(col)
{}

Gui::Message::~Message(){
    free(text);
}