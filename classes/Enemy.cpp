#include "Enemy.hpp"

Enemy::Enemy(Map *map, Player *p, int type, int yLoc){
    this->type = type;
    this->map = map;
    this->yLoc = yLoc;
    this->p = p;
    this->xLoc = map->get_width()-2;
    if(type == 1){
        this->ch = '#';
        lives = 2;
    } 
    else if(type == 2){
        this->ch = '&';
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

void Enemy::mvup_2(int nY){
    while(map->is_blank(yLoc-1, xLoc) && nY >= 0){
        nY--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        yLoc--;
        this->display();
        usleep(100000);
    }
}

void Enemy::mvdown_2(int nY){
    while(map->is_blank(yLoc+1, xLoc) && nY >= 0){
        nY--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        yLoc++;
        this->display();
        usleep(100000);
    }
}

void Enemy::mvleft_2(int nX){
    while(map->is_blank(yLoc, xLoc+1) && nX >= 0){
        nX--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        xLoc++;
        this->display();
        usleep(100000);
    }
}

void Enemy::mvright_2(int nX){
    while(map->is_blank(yLoc, xLoc-1) && nX >= 0){
        nX--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        xLoc--;
        this->display();
        usleep(100000);
    }
}

void Enemy::mvup_1(int nY){
    while(mvwinch(map->getWin(), yLoc-1, xLoc) != '@' && nY >= 0 && yLoc > 1){
        nY--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        yLoc--;
        this->display();
        usleep(30000);
    }
}

void Enemy::mvdown_1(int nY){
    while(mvwinch(map->getWin(), yLoc+1, xLoc) != '@' && nY >= 0 && yLoc < map->get_height()-2){
        nY--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        yLoc++;
        this->display();
        usleep(30000);
    }
}

void Enemy::mvleft_1(int nX){
    while(mvwinch(map->getWin(), yLoc, xLoc-1) != '@' && nX >= 0 && xLoc > map->get_beg_x()+1){
        nX--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        xLoc--;
        this->display();
        usleep(30000);
    }
}

void Enemy::mvright_1(int nX){
    while(mvwinch(map->getWin(), yLoc, xLoc+1) != '@' && nX >= 0 && xLoc < map->get_width()-2){
        nX--;
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        xLoc++;
        this->display();
        usleep(30000);
    }
}


void Enemy::mv_2(){
    srand(time(NULL));
    int mv = rand()%4;
    int nY = rand()% map->get_height()/2+1;
    int nX = rand()% map->get_width()/12+1;
    if(mv == 0) this->mvup_2(nY);
    else if(mv == 1) this->mvdown_2(nY); 
    else if(mv == 2) this->mvleft_2(nX);
    else if(mv == 3) this->mvright_2(nX); 
}

void Enemy::mv_1(){
    srand(time(NULL));
    int mv = rand() % 8;
    int nY = rand() % map->get_height()/2+1;
    int nX = rand() % map->get_width()/1.2 + map->get_width()/7;

    if(mv == 0) mvup_1(nY);
    else if(mv == 1) mvdown_1(nY);
    else if(mv >= 2 && mv <= 4) mvright_1(nX);
    else if(mv >= 5 && mv <= 7) mvleft_1(nX); 
}

void Enemy::mvup_3(){
    int distance = rand() % 3 + 3;

    if(p->get_yLoc()-distance > map->get_beg_y()+1){
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        wrefresh(map->getWin());
        sleep(1);
        xLoc = p->get_xLoc();
        yLoc = p->get_yLoc()-distance;
        this->display();
    }
}

void Enemy::mvdown_3(){
    int distance = rand() % 3 + 3;

    if(p->get_yLoc()+distance < map->get_height()-1){
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        wrefresh(map->getWin());
        sleep(1);
        xLoc = p->get_xLoc();
        yLoc = p->get_yLoc()+distance;
        this->display();
    }
}

void Enemy::mvleft_3(){
    int distance = rand() % 3 + 3;

    if(p->get_xLoc()-distance > map->get_beg_x()+1){
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        wrefresh(map->getWin());
        sleep(1);
        xLoc = p->get_xLoc()-distance;;
        yLoc = p->get_yLoc();
        this->display();
    }
}

void Enemy::mvright_3(){
    int distance = rand() % 3 + 3;

    if(p->get_xLoc()+distance < map->get_width()-1){
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        wrefresh(map->getWin());
        sleep(1);
        xLoc = p->get_xLoc()+distance;;
        yLoc = p->get_yLoc();
        this->display();
    }
}

void Enemy::mv_3(){
    srand(time(NULL));

    int cPoint = rand()%4;

    if(cPoint == 0){
        mvup_3();
    }
    else if(cPoint == 1){
        mvdown_3();
    }
    else if(cPoint == 2){
        mvright_3();
    }
    else if(cPoint == 3){
        mvleft_3();
    }
}

yx Enemy::shoot_2(){
    int xL = this->xLoc-1;

    while(map->is_blank(yLoc, xL-1)){
        if(xL != xLoc-1) mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
        mvwaddch(this->map->getWin(), this->yLoc, xL, '-');
        wrefresh(this->map->getWin());
        xL--;
        
        usleep(30000);
    }
    mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
    wrefresh(this->map->getWin());

    yx c;
    c.x = xL-1;
    c.y = yLoc;

    return c;
}

yx Enemy::shoot_1(){
    int xL = this->xLoc-1;

    int i = 0;
    while(map->is_blank(yLoc, xL) && i < 10){
        if(xL != xLoc-1) mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
        mvwaddch(this->map->getWin(), this->yLoc, xL, 'O');
        wrefresh(this->map->getWin());
        xL--;
        i++;

        usleep(30000);
    }
    mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
    wrefresh(this->map->getWin());

    yx c;
    c.x = xL;
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
    if(lives <= 0){
        mvwaddch(map->getWin(), yLoc, xLoc, '*');
        wrefresh(map->getWin());
        sleep(1);
        mvwaddch(map->getWin(), yLoc, xLoc, ' ');
        wrefresh(map->getWin());
    } 
}

bool Enemy::dead(){
    if(lives <= 0) return true;
    else return false;
}

int Enemy::get_lives(){
    return this->lives;
}

yx Enemy::shoot(){
    if(this->type == 1) return shoot_1();
    else if(this->type == 2) return shoot_2();
    else return shoot_1();
}

void Enemy::mv(){
    if(type == 1) mv_1();
    else if(type == 2) mv_2();
    this_thread::sleep_for(chrono::milliseconds(500));
}


