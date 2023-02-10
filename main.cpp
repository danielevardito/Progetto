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

    srand(time(NULL));

    p_b_list list = new b_list;
    list->next = NULL;
    list->prev = NULL;

    MainWin *main_win = new MainWin();
    main_win->draw_empty();

    PlayMenu *pm = new PlayMenu(main_win);

    Map *map = new Map(main_win);
    Player *p = new Player(main_win, map);
    int play = pm->menu();
    map_prop mp;
    Game *g;

    while(play == 0){
        game_prop gp;
    
        do{ 
            if(gp.won == 1){
                p->increase_coins(4);
                p->reset_yxLoc();
                p->market();
                map = new Map(main_win);
            }
            map_prop mp;
            if (list->prev != NULL) g = new Game(main_win, map, p, list, 0);
            else g = new Game(main_win, map, p, list, 2);
            p->new_game(map, p->get_weapon(), p->get_w_speed());
            p->display();
            gp = g->play_game();

            list->gp = gp;

            list->next = new b_list;
            list->next->prev = list;

            if(gp.won == 2){
                g = new Game(main_win, map, p, list, 1);
                p->display();
                g->play_game();
                p->new_game(map, list->gp.pp.weapon, list->gp.pp.w_speed);
                p->set_lives(list->gp.pp.lives);
                p->set_coins(list->gp.pp.coins);
            }

        
            if(gp.won != 2){
                list = list->next;

                while(list->gp.mp.nMap == list->prev->gp.mp.nMap){
                    list->gp.mp.nMap = rand()%9+1;
                }
            }
            
                        
        }while(gp.won >= 1);

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