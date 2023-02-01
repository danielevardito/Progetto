#include "classes/PlayMenu.hpp"
#include "classes/Game.hpp"
#include "classes/StatsWin.hpp"

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

    Map *map = new Map(main_win);
    
    WINDOW *map_win = map->getWin();

    int n = rand() % 6 + 1;

    map->draw_n_map(n);
    StatsWin *sw = new StatsWin(main_win);
    Player *p = new Player(map, sw);

    //sw->display(p->get_lives(), p->get_coins());
    WINDOW *w = newwin(1,2,2,1);

    do{
        p->display();
        wrefresh(map_win);
    }while(p->getmv() != 'x');

    getch();

    endwin();

    return 0;
}