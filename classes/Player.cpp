#include "Player.hpp"

Player::Player(Map *map){
    this->map = map;
    this->xMax = map->get_width();
    this->yMax = map->get_height();
    this->xLoc = 0;
    this->yLoc = yMax/2;
    this->ch = '@';
    this->leftChar = ' ';

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
          break;

        case KEY_RIGHT:
          this->mvright();
          break;
        
        default:
          break;
    }

    return choice;
}

void Player::display(){
    mvwaddch(this->map->getWin(), this->yLoc, this->xLoc, this->ch);
}