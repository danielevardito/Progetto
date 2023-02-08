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

    PlayMenu *pm = new PlayMenu(main_win);

    int play = pm->menu();

    if(play == 0){
        Map *map = new Map(main_win);
        Player *p = new Player(main_win, map);
        Game *g = new Game(main_win, map, p);

        int won = g->play_game();

        if(won == 1){
            p->increase_coins(5);
            map = new Map(main_win);
            p->new_game(map, 1, 2);
            g = new Game(main_win, map, p);

            won = g->play_game();
        }

        if(won == 1){
            p->increase_coins(5);
            map = new Map(main_win);
            p->new_game(map, 1, 3);
            g = new Game(main_win, map, p);

            won = g->play_game();
        }

        if(won == 1){
            p->increase_coins(5);
            map = new Map(main_win);
            p->new_game(map, 2, 1);
            g = new Game(main_win, map, p);

            won = g->play_game();
        }

        if(won == 1){
            p->increase_coins(5);
            map = new Map(main_win);
            p->new_game(map, 2, 2);
            g = new Game(main_win, map, p);

            won = g->play_game();
        }

        if(won == 1){
            p->increase_coins(5);
            map = new Map(main_win);
            p->new_game(map, 2, 3);
            g = new Game(main_win, map, p);

            won = g->play_game();
        }

        if(won == 1){
            p->increase_coins(5);
            map = new Map(main_win);
            p->new_game(map, 3, 1);
            g = new Game(main_win, map, p);

            won = g->play_game();
        }

        if(won == 1){
            p->increase_coins(5);
            map = new Map(main_win);
            p->new_game(map, 3, 2);
            g = new Game(main_win, map, p);

            won = g->play_game();
        }

        if(won == 1){
            p->increase_coins(5);
            map = new Map(main_win);
            p->new_game(map, 3, 3);
            g = new Game(main_win, map, p);

            won = g->play_game();
        }
        
    }

    endwin();

    return 0;
}