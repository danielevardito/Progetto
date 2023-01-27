#include "classes/MainWin.hpp"
#include "classes/PlayMenu.hpp"
#include "classes/Map.hpp"


using namespace std;

/*
MAIN DEL PROGETTO, coordina tutte le classi e
permette il funzionamento del programma.
*/

int main(){

    initscr();
    noecho();
    curs_set(0);

    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    MainWin *main_win = new MainWin();
    main_win->draw_empty();

    Map *map = new Map(main_win->get_height(), main_win->get_width(), main_win->get_beg_y(), main_win->get_beg_x());
    /*
    int height5 = map->get_height()/5;
    int width15 = map->get_width()/15;
    WINDOW *win = map->getWin(); 
    mvwhline(win, height5*4, width15*11, ACS_HLINE, width15*5);
    */
    map->draw_map4();
    //wrefresh(win);

    refresh();
    
    getch();

    endwin();

    return 0;
}