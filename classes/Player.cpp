#include "Player.hpp"

Player::Player(MainWin *mw, Map *map, int weapon){
    this->map = map;
    this->sw = new StatsWin(mw);
    this->xMax = map->get_width();
    this->yMax = map->get_height();
    this->xLoc = 1;
    this->yLoc = yMax/2;
    this->ch = '@';
    this->leftChar = ' ';

    this->weapon = weapon;

    keypad(map->getWin(), true);
}

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

void Player::display(){
    mvwaddch(this->map->getWin(), this->yLoc, this->xLoc, this->ch);
}

void Player::decrease_lives(){
    this->lives--;
}

void Player::increase_coins(int coins){
    this->coins += coins;
}

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

void Player::new_game(Map *map, int weapon){
    this->map = map;
    this->xMax = map->get_width();
    this->yMax = map->get_height();
    keypad(map->getWin(), true);

    this->xLoc = 1;
    this->yLoc = yMax/2;
}

StatsWin* Player::get_stats_win(){
    return this->sw;
}

void Player::shoot_1(int speed){
    if(speed == 1) speed = 60;
    else if(speed == 2) speed = 30;
    else if(speed == 3)  speed = 15;
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
    }
}

void Player::shoot_2(int speed){
    if(speed == 1) speed = 70;
    else if(speed == 2) speed = 35;
    else if(speed == 3)  speed = 25;
    if(this->last_pressed_x == KEY_RIGHT || this->last_pressed_x == 0){
        int xS = this->xLoc+1;
        int breaks = 0;
        timeout(speed);
        while(breaks <= 1 && xS < this->map->get_width()-1){
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
    }
    else if(this->last_pressed_x == KEY_LEFT){
        int xS = this->xLoc-1;
        int breaks = 0;
        timeout(speed);
        while(breaks <= 1 && xS > 0){
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
    }
}

void Player::shoot_3(int speed){
    if(speed == 1) speed = 85;
    else if(speed == 2) speed = 70;
    else if(speed == 3)  speed = 50;

    if(this->last_pressed_x == KEY_RIGHT || this->last_pressed_x == 0){
        int xS = this->xLoc+1;
        timeout(speed);
        while(xS < this->map->get_width()-1){
            getch();
            if(xS != xLoc+1) mvwaddch(this->map->getWin(), this->yLoc, xS-1, ' ');
            mvwaddch(this->map->getWin(), this->yLoc, xS, 'Z');
            wrefresh(this->map->getWin());
            xS++;
        }
        mvwaddch(this->map->getWin(), this->yLoc, xS-1, ' ');
        wrefresh(this->map->getWin());

        timeout(-1);
    }
    else if(this->last_pressed_x == KEY_LEFT){
        int xS = this->xLoc-1;
        int breaks = 0;
        timeout(speed);
        while(xS > 0){
            getch();
            if(xS != xLoc-1) mvwaddch(this->map->getWin(), this->yLoc, xS+1, ' ');
            mvwaddch(this->map->getWin(), this->yLoc, xS, 'Z');
            wrefresh(this->map->getWin());
            xS--;
        }
        mvwaddch(this->map->getWin(), this->yLoc, xS+1, ' ');
        wrefresh(this->map->getWin());

        timeout(-1);
    }
}