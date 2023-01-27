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

    PlayMenu *pm = new PlayMenu(main_win->get_height(), main_win->get_width(), main_win->get_beg_y(), main_win->get_beg_x());

    int n = pm->menu();

    printw("%d", n);
    refresh();
    
    endwin();

    return 0;
}