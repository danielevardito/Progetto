#include "Enemy.hpp"

Enemy::Enemy(Map *map, Player *p, int type, int yLoc){
    this->type = type;
    this->map = map;
    this->yLoc = yLoc;
    this->p = p;
    this->xLoc = map->get_width()-2;
    if(type == 1){
        this->ch = '&';
        lives = 2;
    } 
    else if(type == 2){
        this->ch = '#';
        lives = 2;
    } 
    else if(type == 3){
        this->ch = '?';
        lives = 3;
    } 
    else if(type == 4){
        this->ch = '!';
        lives = 5;
    } 
}

void Enemy::display(){
    mvwaddch(this->map->getWin(), yLoc, xLoc, ch);
    wrefresh(map->getWin());
}

void Enemy::mvup_1(int nY){
    while(map->is_blank(yLoc-1, xLoc) && nY >= 0){
        nY--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        yLoc--;
        this->display();
        usleep(100000);
    }
}

void Enemy::mvdown_1(int nY){
    while(map->is_blank(yLoc+1, xLoc) && nY >= 0){
        nY--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        yLoc++;
        this->display();
        usleep(100000);
    }
}

void Enemy::mvleft_1(int nX){
    while(map->is_blank(yLoc, xLoc+1) && nX >= 0){
        nX--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        xLoc++;
        this->display();
        usleep(100000);
    }
}

void Enemy::mvright_1(int nX){
    while(map->is_blank(yLoc, xLoc-1) && nX >= 0){
        nX--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        xLoc--;
        this->display();
        usleep(100000);
    }
}

void Enemy::mv_1(){
    srand(time(NULL));
    int mv = rand()%4;
    int nY = rand()% map->get_height()/2+1;
    int nX = rand()% map->get_width()/12+1;
    if(mv == 0) this->mvup_1(nY);
    if(mv == 1) this->mvdown_1(nY); 
    if(mv == 2) this->mvleft_1(nX);
    if(mv == 3) this->mvright_1(nX); 
}

yx Enemy::shoot_1(){
    int xL = this->xLoc-1;

    while(map->is_blank(yLoc, xL-1)){
        if(xL != xLoc-1) mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
        mvwaddch(this->map->getWin(), this->yLoc, xL, '-');
        wrefresh(this->map->getWin());
        xL--;
        
        usleep(50000);
    }
    mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
    wrefresh(this->map->getWin());

    yx c;
    c.x = xL-1;
    c.y = yLoc;

    return c;
}

int Enemy::get_xLoc(){
    return this->xLoc;
}

int Enemy::get_yLoc(){
    return this->yLoc;
}

void Enemy::decrease_lives(){
    lives--;
    if(lives <= 0) mvaddch(yLoc, xLoc, ' ');
}

bool Enemy::dead(){
    if(lives <= 0) return true;
    else return false;
}

int Enemy::get_lives(){
    return this->lives;
}


