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

    map->draw_map1();
/*
    int lX = rand() % map->get_width()/4 +2;
    int lY = rand() % map->get_height()/4 + 2;
    int sX = map->get_width() - lX /2;
    int sY = map->get_height() - lY /2;

    for(int i = sY; i < lY; i++){
        for(int j = sX; j < lX; j++){
            mvwprintw(map->getWin(), i, j, "=");
        }
    }
*/
    refresh();
    
    getch();

    endwin();

    return 0;
}