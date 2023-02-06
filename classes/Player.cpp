#include "Player.hpp"

/*
Costrutture di Player: viene settata la mappa del giocatore, i parametri di posizione, il carattere
rappresentante il player, e arma e velocità di arma base.
*/
Player::Player(MainWin *mw, Map *map){
    this->map = map;
    this->sw = new StatsWin(mw);
    this->xMax = map->get_width();
    this->yMax = map->get_height();
    this->xLoc = 1;
    this->yLoc = yMax/2;
    this->ch = '@';
    this->leftChar = ' ';

    this->weapon = 1;
    this->w_speed = 1;

    keypad(map->getWin(), true);
}

/*
Le quattro funzioni modificano la posizione del player, che sarà visualizzata nel metodo display
*/
void Player::mvup(){
    if(map->is_blank(yLoc-1, xLoc)){
        mvwaddch(this->map->getWin(), this->yLoc, this->xLoc, this->leftChar);
        this->yLoc--;
        if(this->yLoc < 0) this->yLoc = 0;
    }
}

void Player::mvdown(){
    if(map->is_blank(yLoc+1, xLoc)){
        mvwaddch(this->map->getWin(), this->yLoc, this->xLoc, this->leftChar);
        this->yLoc++;
        if(this->yLoc > this->yMax-1) this->yLoc = this->yMax-1;
    }
}

void Player::mvleft(){
    if(map->is_blank(yLoc, xLoc-1)){
        mvwaddch(this->map->getWin(), this->yLoc, this->xLoc, this->leftChar);
        this->xLoc--;
        if(this->xLoc < 0) this->xLoc = 0;
    }
}

void Player::mvright(){
    if(map->is_blank(yLoc, xLoc+1)){
        mvwaddch(this->map->getWin(), this->yLoc, this->xLoc, this->leftChar);
        this->xLoc++;
        if(this->xLoc > this->xMax-1) this->xLoc = this->xMax-1;
    }
}

/*
Se viene premuta una freccetta, il Player si muoverà di conseguenza
*/
int Player::getmv(){
    int choice = wgetch(this->map->getWin());

    switch(choice){
        case KEY_UP:
          this->mvup();
          break;

        case KEY_DOWN:
          this->mvdown();
          break;

        case KEY_LEFT:
          this->mvleft();
          this->last_pressed_x = KEY_LEFT;
          break;

        case KEY_RIGHT:
          this->mvright();
          this->last_pressed_x = KEY_RIGHT;
          break;
        
        default:
          break;
    }

    return choice;
}

/*
fa visualizzare il Player nella mappa, è usato generalemente dopo un getmv
*/
void Player::display(){
    mvwaddch(this->map->getWin(), this->yLoc, this->xLoc, this->ch);
}

/*
Diminuisce le vite del Player, avviene quando viene colpito
*/
void Player::decrease_lives(){
    this->lives--;
}

/*
Aumenta i soldi del player in base al parametro
*/
void Player::increase_coins(int coins){
    this->coins += coins;
}

/*
Diminuisce i soldi in base al parametro
*/
bool Player::decrease_coins(int coins){
    bool decreased = false;

    if(this->coins >= coins){
        this->coins -= coins;
    }

    return decreased;
}

int Player::get_coins(){
    return this->coins;
}

int Player::get_lives(){
    return this->lives;
}

int Player::get_weapon(){
    return this->weapon;
}

int Player::get_w_speed(){
    return this->w_speed;
}

/*
Prepara il player alla nuovo livello, con le armi prese dal market
*/
void Player::new_game(Map *map, int weapon, int w_speed){
    this->map = map;
    this->weapon = weapon;
    this->w_speed = w_speed;
    this->xMax = map->get_width();
    this->yMax = map->get_height();
    keypad(map->getWin(), true);

    this->xLoc = 1;
    this->yLoc = yMax/2;
}

StatsWin* Player::get_stats_win(){
    return this->sw;
}

/*
Spara un proiettile che non può perforare la mappa, viene sparato a destra o sinistra in base
all'ultimo movimento del player.
*/
yx Player::shoot_1(){
    int speed;
    yx c;
    if(w_speed == 1) speed = 60;
    else if(w_speed == 2) speed = 30;
    else if(w_speed == 3)  speed = 15;
    if(this->last_pressed_x == KEY_RIGHT || this->last_pressed_x == 0){
        int xS = this->xLoc+1;

        timeout(speed);
        while(map->is_blank(yLoc, xS)){
            getch();
            if(xS != xLoc+1) mvwaddch(this->map->getWin(), this->yLoc, xS-1, ' ');
            mvwaddch(this->map->getWin(), this->yLoc, xS, '>');
            wrefresh(this->map->getWin());
            xS++;
        }
        mvwaddch(this->map->getWin(), this->yLoc, xS-1, ' ');
        wrefresh(this->map->getWin());
        
        timeout(-1);

        c.y = yLoc;
        c.x = xS;
    }
    else if(this->last_pressed_x == KEY_LEFT){
        int xS = this->xLoc-1;

        timeout(speed);
        while(map->is_blank(yLoc, xS)){
            getch();
            if(xS != xLoc-1) mvwaddch(this->map->getWin(), this->yLoc, xS+1, ' ');
            mvwaddch(this->map->getWin(), this->yLoc, xS, '<');
            wrefresh(this->map->getWin());
            xS--;
        }
        mvwaddch(this->map->getWin(), this->yLoc, xS+1, ' ');
        wrefresh(this->map->getWin());

        timeout(-1);
        c.y = yLoc;
        c.x = xS;
    }
    return c;
}

/*
Spara un proiettile in grado di rompere un solo muro presente nella mappa, al prossimo si disintegra
viene sparato a destra o sinistra in base all'ultimo movimento del player
*/
yx Player::shoot_2(){
    int speed;
    yx c;
    if(w_speed == 1) speed = 70;
    else if(w_speed == 2) speed = 35;
    else if(w_speed == 3)  speed = 25;
    if(this->last_pressed_x == KEY_RIGHT || this->last_pressed_x == 0){
        int xS = this->xLoc+1;
        int breaks = 0;
        timeout(speed);
        while(breaks <= 1 && xS < this->map->get_width()-1 && !hitted(yLoc, xS)){
            getch();
            if(xS != xLoc+1) mvwaddch(this->map->getWin(), this->yLoc, xS-1, ' ');
            mvwaddch(this->map->getWin(), this->yLoc, xS, '|');
            wrefresh(this->map->getWin());
            xS++;
            if(!map->is_blank(yLoc, xS)) breaks++;
        }
        mvwaddch(this->map->getWin(), this->yLoc, xS-1, ' ');
        wrefresh(this->map->getWin());

        timeout(-1);

        c.y = yLoc;
        c.x = xS;
    }
    else if(this->last_pressed_x == KEY_LEFT){
        int xS = this->xLoc-1;
        int breaks = 0;
        timeout(speed);
        while(breaks <= 1 && xS > 0 && !hitted(yLoc, xS)){
            getch();
            if(xS != xLoc-1) mvwaddch(this->map->getWin(), this->yLoc, xS+1, ' ');
            mvwaddch(this->map->getWin(), this->yLoc, xS, '|');
            wrefresh(this->map->getWin());
            xS--;
            if(!map->is_blank(yLoc, xS)) breaks++;
        }
        mvwaddch(this->map->getWin(), this->yLoc, xS+1, ' ');
        wrefresh(this->map->getWin());

        timeout(-1);

        c.y = yLoc;
        c.x = xS;
    }

    return c;
}

/*
Proiettile in grado di rompere ogni muro della mappa eccetto i limiti.
Viene sparato a destra o sinistra in base all'ultimo movimento del player
*/
yx Player::shoot_3(){
    int speed;
    if(w_speed == 1) speed = 85;
    else if(w_speed == 2) speed = 70;
    else if(w_speed == 3)  speed = 50;

    yx c;

    if(this->last_pressed_x == KEY_RIGHT || this->last_pressed_x == 0){
        int xS = this->xLoc+1;
        timeout(speed);
        while(xS < this->map->get_width()-1 && !hitted(yLoc, xS)){
            getch();
            if(xS != xLoc+1) mvwaddch(this->map->getWin(), this->yLoc, xS-1, ' ');
            mvwaddch(this->map->getWin(), this->yLoc, xS, 'Z');
            wrefresh(this->map->getWin());
            xS++;
        }
        mvwaddch(this->map->getWin(), this->yLoc, xS-1, ' ');
        wrefresh(this->map->getWin());

        timeout(-1);

        c.y = yLoc;
        c.x = xS;
    }
    else if(this->last_pressed_x == KEY_LEFT){
        int xS = this->xLoc-1;
        int breaks = 0;
        timeout(speed);
        while(xS > 0 && !hitted(yLoc, xS)){
            getch();
            if(xS != xLoc-1) mvwaddch(this->map->getWin(), this->yLoc, xS+1, ' ');
            mvwaddch(this->map->getWin(), this->yLoc, xS, 'Z');
            wrefresh(this->map->getWin());
            xS--;
        }
        mvwaddch(this->map->getWin(), this->yLoc, xS+1, ' ');
        wrefresh(this->map->getWin());

        timeout(-1);

        c.y = yLoc;
        c.x = xS;
    }

    return c;
}

/*
spara in base all'arma del player
*/
yx Player::shoot(){
    yx c;
    if(weapon == 1) c = shoot_1();
    else if(weapon == 2) c = shoot_2();
    else if(weapon == 3) c = shoot_3();
    //usleep(200000);

    return c;
}

int Player::get_xLoc(){
    return this->xLoc;
}

int Player::get_yLoc(){
    return this->yLoc;
}

bool Player::hitted(int y, int x){
    if(mvwinch(map->getWin(), y, x) == '&') return true;
    else if(mvwinch(map->getWin(), y, x) == '#') return true;
    else if(mvwinch(map->getWin(), y, x) == '?') return true;
    else if(mvwinch(map->getWin(), y, x) == '!') return true;
    else return false;
}