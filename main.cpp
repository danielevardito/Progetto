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
    Player *p = new Player(main_win, map, 0);
    Game *g = new Game(main_win, map, p);

    bool won = g->play_game();

    map = new Map(main_win);
    p->new_game(map, 0);
    g = new Game(main_win, map, p);

    won = g->play_game();

    endwin();

    return 0;
}