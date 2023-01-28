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
    WINDOW *win = map->getWin();

    int n = rand() % 6 + 1;

    map->draw_n_map(n);

    getch();

    endwin();

    return 0;
}