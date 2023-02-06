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
            nEnemies = 1;
        }

        if(p->get_w_speed() == 2){
            int y = map->get_height()/2-2;
            nEnemies = 2;
            for(int i = 0; i < nEnemies; i++){
                enemies[i] = new Enemy(map, p, 1, y);
                enemies[i]->display();
                y++;
            }
        }

        if(p->get_w_speed() == 3){
            int y = map->get_height()/2;
            nEnemies = 1;
            enemies[0] = new Enemy(map, p, 2, y);
        }
    }

    if(p->get_weapon() == 2){
        if(p->get_w_speed() == 1){
            int y = map->get_height()/2-1;

            nEnemies = 3;
            for(int i = 0; i < nEnemies; i++){
                enemies[i] = new Enemy(map, p, 2, y);
                y++;
            }
        }

        if(p->get_w_speed() == 2){
            int y = map->get_height()/2-1;

            nEnemies = 4;
            for(int i = 0; i < 2; i++){
                enemies[i] = new Enemy(map, p, 2, y);
                y++;
            }
            enemies[2] = new Enemy(map, p, 3, y);
        }

        if(p->get_w_speed() == 3){
            int y = map->get_height()/2-2;

            nEnemies = 5;
            for(int i = 0; i < 3; i++){
                enemies[i] = new Enemy(map, p, 2, y);
                y++;
            }
            for(int i = 2; i < 4; i++){
                enemies[i] = new Enemy(map, p, 3, y);
                y++;
            }
        }
    }

    if(p->get_weapon() == 3){
        if(p->get_w_speed() == 1){
            nEnemies = 4;
            int y = map->get_height()/2-2;
            for(int i = 0; i < 3; i++){
                enemies[i] = new Enemy(map, p, 3, y);
                y++;
            }
            enemies[3] = new Enemy(map, p, 4, y);
        }

        if(p->get_w_speed() == 2){
            nEnemies = 8;
            int y = map->get_height()/2-4;
            for(int i = 0; i < 5; i++){
                enemies[i] = new Enemy(map, p, 4, y);
                y++;
            }

            for(int i = 5; i < 8; i++){
                enemies[i] = new Enemy(map, p, 3, y);
                y++;
            }
        }

        if(p->get_w_speed() == 3){
            nEnemies = map->get_height()-2;
            int y = 1;

            for(int i = 0; i < nEnemies; i++){
                enemies[i] = new Enemy(map, p, 4, y);
                y++;
            }
        }

    }
    
    int n = rand()%6+1;

    map->draw_n_map(n);
    p->get_stats_win()->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());

    for(int i = 0; i < nEnemies; i++){
        enemies[i]->display();
    }

    int j = 10;
    for(int i = 0; i < nEnemies; i++){
        intervals[i] = j;
        j += 3;
    }

    p->display();
}

bool Game::all_dead(int i = 0){
    if(i == nEnemies) return true;
    if(enemies[i]->dead()) return true && all_dead(i+1);
    else return false;
}

/*
Si svolge una partita, il metodo restituisce true se il giocatore ha vinto, false se ha perso
All'interno di essa vengono gestiti i comandi per sparare, diminuire la vita ecc..
Vengono gestite le interazioni tra player e nemici.
*/
int Game::play_game(){
    int won = 2;

    int i = 0;
    while(won == 2){
        if(this->all_dead()){
            won = 1;
        }
        else{
            char c = this->p->getmv();
            if(c == 'x'){
            p->decrease_lives();
            sw->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());
            } 
            for(int j = 0; j < this->nEnemies; j++){
                if(!enemies[j]->dead()){
                    if(i % intervals[j] == 0){
                        p->display();
                        enemies[j]->mv();
                    }
                    int n = rand()% 15 + intervals[j]*5;
                    if(i % n == 0){
                        yx c = enemies[j]->shoot();
                        if(c.y == p->get_yLoc() && c.x == p->get_xLoc()){
                            p->decrease_lives();
                            sw->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());
                        }
                    }
                }
                
            }

            if(c == 's'){
                yx cP = p->shoot();
                for(int j = 0; j < nEnemies; j++){
                    if(cP.y == enemies[j]->get_yLoc() && cP.x == enemies[j]->get_xLoc()){
                        enemies[j]->decrease_lives();
                    }
                }
            }
            if(p->get_lives() == 0){
                won = 0;
                sleep(2);
            }
            else if(c == 'w'){
                won = 1;
            }
            else p->display();
            i++;
        }
    }

    return won;
}

int Game::enemies_size(){
    int i = 0;

    while(this->enemies[i] != NULL){
        i++;
    }

    return i;
}