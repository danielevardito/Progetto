#include "Game.hpp"

/*
assegno mappa e player (che avrà le statistiche in base alla precedente partita e a ciò che ha acquistato nel market)
disegno la mappa e la finestra delle statistiche
*/
Game::Game(MainWin *mw, Map *map, Player *p){
    srand(time(NULL));

    this->p = p;
    this->map = map;
    this->sw = p->get_stats_win();
    
    int n = rand()%6+1;

    map->draw_n_map(n);
    p->get_stats_win()->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());

    p->display();
}

/*
Si svolge una partita, il metodo restituisce true se il giocatore ha vinto, false se ha perso
All'interno di essa vengono gestiti i comandi per sparare, diminuire la vita ecc..
Vengono gestite le interazioni tra player e nemici.
*/
bool Game::play_game(){
    bool won = false;

    while(p->get_lives() > 0 && !won){
        char c = this->p->getmv();
        if(c == 'x'){
            p->decrease_lives();
            sw->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());
        } 
        if(c == 's'){
            p->shoot();
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