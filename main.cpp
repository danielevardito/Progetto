#include "classes/MainWin.hpp"
#include "classes/PlayMenu.hpp"

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

    WINDOW *play_menu = newwin(main_win->get_height()-2, main_win->get_width()-2, main_win->get_beg_y()+1, main_win->get_beg_x()+1);
    box(play_menu, 0, 0);
    refresh();
    wrefresh(play_menu);

    int height, width, y0, x0;
    getmaxyx(play_menu, height, width);
    getbegyx(play_menu, y0, x0);

    PlayMenu *pm = new PlayMenu(height, width, y0, x0);

    pm->draw_menu();
    
    endwin();

    return 0;
}