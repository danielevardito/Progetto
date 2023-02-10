#include "Game.hpp"

/*
assegno mappa e player (che avrà le statistiche in base alla precedente partita e a ciò che ha acquistato nel market)
disegno la mappa e la finestra delle statistiche
*/
Game::Game(MainWin *mw, Map *map, Player *p, p_b_list list, int prev){
    this->prev = prev;
    if(prev == 0 || prev == 2){
        srand(time(NULL));

        this->p = p;
        p->reset_yxLoc();
        this->map = map;
        this->sw = p->get_stats_win();

    /*
    seleziona la difficoltà del gioco in base al tipo e alla velocità dell'arma
    */
        select_diff();
    /*
    scrive una mappa selezionata randomicamente
    */

        gp.mp = map->draw_n_map(list->gp.mp.nMap);
        p->get_stats_win()->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());

        for(int i = 0; i < nEnemies; i++){
            enemies[i]->display();
        }

        int j = 25;
        for(int i = 0; i < nEnemies; i++){
            intervals[i] = j;
            j *= 1.9;
        }

        p->display();
    }
    else{
        srand(time(NULL));

        this->p = p;
        p->new_game(map, list->prev->gp.pp.weapon, list->prev->gp.pp.w_speed);
        p->set_coins(list->prev->gp.pp.coins);
        p->set_lives(list->prev->gp.pp.lives);
        p->reset_yxLoc();
        this->map = map;
        this->sw = p->get_stats_win();

    /*
    seleziona la difficoltà del gioco in base al tipo e alla velocità dell'arma
    */
        select_diff();
    /*
    scrive una mappa selezionata randomicamente
    */

        map->draw_n_cp_map(list->prev->gp.mp);
        p->get_stats_win()->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());

        for(int i = 0; i < nEnemies; i++){
            enemies[i]->display();
        }

        int j = 25;
        for(int i = 0; i < nEnemies; i++){
            intervals[i] = j;
            j *= 1.9;
        }

        p->display();
    }
    
}

/*
metodo ricorsivo che verifica se i nemici sono tutti morti, per decretare la vittoria
*/
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
game_prop Game::play_game(){
    int won = 3;
    int i = 0; //contatore che serve a decidere quando far muovere i nemici
    double interv = 2.5; //moltiplicatore che serve a dimimnuire o aumentare i numero di movimenti di nemici
    while(won == 3){ //ciclo che funziona finchè won non abbia un risultato

/*
se i nemici sono tutti morti, hai vinto
*/
        if(this->all_dead()){
            usleep(500000);
            won = 1;
        }
/*
se le vite del player sono 0, hai perso
*/
        else if(p->get_lives() == 0){
            won = 0;
            sleep(2);
        }
        else{
            char c = this->p->getmv();

            if(prev == 0){
                if(c == 'e' || c == 'E'){
                    won = 2;
                }
            } 
            
            /*
            if(c == 'x'){
            p->decrease_lives();
            sw->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());
            } 
            */
            p->display();
            /*
            cicli che agiscono per ogni nemico presente nella partita
            */
            for(int j = 0; j < nEnemies; j++){
                if(!enemies[j]->dead()) enemies[j]->display();
            }
            for(int j = 0; j < this->nEnemies && p->get_lives() != 0; j++){
                if(!enemies[j]->dead()){
                    /*
                    momento in cui si muove e spara il nemico
                    */
                    if(i % intervals[j] == 0){
                        p->display();
                        keypad(map->getWin(), false);
                        enemies[j]->mv();
                        yx c = enemies[j]->shoot();
                        /*
                        una volta sparato, verifica se si è colpito il player e in tal caso decrementa la vita
                        */
                        if(c.y == p->get_yLoc() && c.x == p->get_xLoc()){
                            if(enemies[j]->get_type() == 4) p->reset_lives();
                            else p->decrease_lives();
                            if(p->get_lives() == 0) {
                                mvwaddch(map->getWin(), p->get_yLoc(), p->get_xLoc(), ' ');
                            }
                            sw->display(p->get_lives(), p->get_coins(), p->get_weapon(), p->get_w_speed());
                        }
                        if(p->get_lives() > 0) keypad(map->getWin(), true);

                        /*
                        diminuisci il moltiplicatore degli intervalli
                        */
                        if(interv >= 0.2){
                            intervals[j]*=interv;
                            interv-=0.1;
                        }
                    }
                        
                }
                
            }

            /*
            se un nemico viene sparato, decrementa la sua vita
            */
            if(c == 's' || c == 'S'){
                yx cP = p->shoot();
                for(int j = 0; j < nEnemies; j++){
                    if(cP.y == enemies[j]->get_yLoc() && cP.x == enemies[j]->get_xLoc()){
                        enemies[j]->decrease_lives();
                    }
                }
            }
            /*
            if(c == 'w'){
                won = 1;
            }
            */
            p->display();
            i++;
        }
    }

    gp.pp.coins = p->get_coins();
    gp.pp.lives = p->get_lives();
    gp.pp.weapon = p->get_weapon();
    gp.pp.w_speed = p->get_w_speed();
    gp.won = won;

    return gp;
}

void Game::select_diff(){
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
            y++;
            enemies[3] = new Enemy(map, p, 3, y);
        }

        if(p->get_w_speed() == 3){
            int y = map->get_height()/2-2;

            nEnemies = 5;
            for(int i = 0; i < 5; i++){
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
                enemies[i] = new Enemy(map, p, 3, y);
                y++;
            }

            for(int i = 5; i < 8; i++){
                enemies[i] = new Enemy(map, p, 4, y);
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
}