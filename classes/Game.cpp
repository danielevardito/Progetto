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

    if(p->get_weapon() == 1){
        if(p->get_w_speed() == 1){
            enemies[0] = new Enemy(map, p, 1, map->get_height()/2);
            enemies[0]->display();
        }

        if(p->get_w_speed() == 2){
            int y = map->get_height()/2-2;
            for(int i = 0; i < 2; i++){
                enemies[i] = new Enemy(map, p, 1, y);
                enemies[i]->display();
                y++;
            }
        }
    }
    
    int n = rand()%6+1;

    map->draw_n_map(n);
    p->get_stats_win()->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());

    enemies[0]->display();
    p->display();
}

/*
Si svolge una partita, il metodo restituisce true se il giocatore ha vinto, false se ha perso
All'interno di essa vengono gestiti i comandi per sparare, diminuire la vita ecc..
Vengono gestite le interazioni tra player e nemici.
*/
bool Game::play_game(){
    bool won = false;

    int i = 0;
    while(p->get_lives() > 0 && !won){
        char c = this->p->getmv();
        if(c == 'x'){
            p->decrease_lives();
            sw->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());
        } 
        
        if(i % 10 == 0){
            p->display();
            enemies[0]->mv_1();
            if(i % 30 == 0){
                yx c = enemies[0]->shoot_1();
                if(c.y == p->get_yLoc() && c.x == p->get_xLoc()){
                    p->decrease_lives();
                    sw->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());
                }
            }
        }
        if(p->get_lives() == 0){
            sleep(2);
        }
        else if(c == 'w'){
            won = true;
        }
        else p->display();
        i++;
    }

    return false;
}

int Game::enemies_size(){
    int i = 0;

    while(this->enemies[i] != NULL){
        i++;
    }

    return i;
}