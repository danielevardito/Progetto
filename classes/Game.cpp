#include "Game.hpp"

Game::Game(MainWin *mw, Map *map, Player *p){
    srand(time(NULL));

    this->p = p;
    this->map = map;
    this->sw = p->get_stats_win();
    
    int n = rand()%6+1;

    map->draw_n_map(n);
    p->get_stats_win()->display(p->get_lives(), p->get_coins());

    p->display();
}

bool Game::play_game(){
    bool won = false;

    while(p->get_lives() > 0 && !won){
        char c = this->p->getmv();
        if(c == 'x'){
            p->decrease_lives();
            sw->display(p->get_lives(), p->get_coins());
        } 
        if(c == 's'){
            p->shoot_3(3);
        }
        if(p->get_lives() == 0){
            sleep(2);
        }
        else if(c == 'w'){
            won = true;
        }
        else p->display();
    }

    return false;
}