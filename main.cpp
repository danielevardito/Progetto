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

    Map *map = new Map(main_win);
    Player *p = new Player(main_win, map);
    int play = pm->menu();
    Game *g = new Game(main_win, map, p);

    while(play == 0){
        int won = 0;
    
        do{ 
            if(won == 1){
                p->increase_coins(4);
                p->reset_yxLoc();
                p->market();
                map = new Map(main_win);
            }
            g = new Game(main_win, map, p);
            p->new_game(map, p->get_weapon(), p->get_w_speed());
            p->display();
            won = g->play_game();
        }while(won == 1);

        main_win->draw_empty();
        map->draw_empty();
        pm = new PlayMenu(main_win);
        play = pm->menu();
        p->set_lives(5);
        p->set_coins(0);
    }

    endwin();

    return 0;
}