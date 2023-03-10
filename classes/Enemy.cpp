#include "Enemy.hpp"

/*
Costruttore, vengono passati mappa player, e posizione in altezza
In base al tipo, inizializza il carattere
*/
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

/*
visualizza il carattere
*/
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

void Enemy::mvup_3(int i = 0){
    if(i < 5){
        int distance = rand() % 2 + 2;

        if(p->get_yLoc()-distance > map->get_beg_y()+1 && !is_occupied(p->get_yLoc()-distance, p->get_xLoc())){
            mvwaddch(map->getWin(), yLoc, xLoc, ' ');
            wrefresh(map->getWin());
            sleep(1);
            xLoc = p->get_xLoc();
            yLoc = p->get_yLoc()-distance;
            this->display();
        }
        else mvup_3(i+1);
        }
}

void Enemy::mvdown_3(int i = 0){
    if(i < 5){
        int distance = rand() % 2 + 2;

        if(p->get_yLoc()+distance < map->get_height()-1 && !is_occupied(p->get_yLoc()+distance, p->get_xLoc())){
            mvwaddch(map->getWin(), yLoc, xLoc, ' ');
            wrefresh(map->getWin());
            sleep(1);
            xLoc = p->get_xLoc();
            yLoc = p->get_yLoc()+distance;
            this->display();
        }
        else mvdown_3();
    }
}

void Enemy::mvleft_3(int i = 0){
    if(i < 5){
        int distance = rand() % 2 + 2;

        if(p->get_xLoc()-distance > map->get_beg_x()+1 && !is_occupied(p->get_yLoc(), p->get_xLoc()-distance)){
            mvwaddch(map->getWin(), yLoc, xLoc, ' ');
            wrefresh(map->getWin());
            sleep(1);
            xLoc = p->get_xLoc()-distance;;
            yLoc = p->get_yLoc();
            this->display();
        }
        else mvleft_3(i+1);
    }
}

void Enemy::mvright_3(int i = 0){
    if(i < 5){
        int distance = rand() % 2 + 2;

        if(p->get_xLoc()+distance < map->get_width()-1 && !is_occupied(p->get_yLoc(), p->get_xLoc()+distance)){
            mvwaddch(map->getWin(), yLoc, xLoc, ' ');
            wrefresh(map->getWin());
            sleep(1);
            xLoc = p->get_xLoc()+distance;;
            yLoc = p->get_yLoc();
            this->display();
        }
        else mvright_3(i+1);
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

void Enemy::mv_4(){
    srand(time(NULL));
    int mv = rand()%2;
    int nY = rand()% map->get_height()/4+1;
    if(mv == 0) this->mvup_2(nY);
    else if(mv == 1) this->mvdown_2(nY); 
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

yx Enemy::shoot_4(){
    int xL = this->xLoc-1;

    while(mvwinch(map->getWin(), yLoc, xL-1) != '@' && xL > 1){
        if(xL != xLoc-1) mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
        mvwaddch(this->map->getWin(), this->yLoc, xL, ']');
        wrefresh(this->map->getWin());
        xL--;
        
        usleep(10000);
    }
    mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
    wrefresh(this->map->getWin());

    yx c;
    c.x = xL-1;
    c.y = yLoc;

    return c;
}

yx Enemy::shoot_left_3(){
    int xL = this->xLoc-1;

    while(map->is_blank(yLoc, xL-1)){
        if(xL != xLoc-1) mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
        mvwaddch(this->map->getWin(), this->yLoc, xL, '-');
        wrefresh(this->map->getWin());
        xL--;
        
        usleep(80000);
    }
    mvwaddch(this->map->getWin(), this->yLoc, xL+1, ' ');
    wrefresh(this->map->getWin());

    yx c;
    c.x = xL-1;
    c.y = yLoc;

    return c;
}

yx Enemy::shoot_right_3(){
    int xL = this->xLoc+1;

    while(map->is_blank(yLoc, xL+1)){
        if(xL != xLoc+1) mvwaddch(this->map->getWin(), this->yLoc, xL-1, ' ');
        mvwaddch(this->map->getWin(), this->yLoc, xL, '-');
        wrefresh(this->map->getWin());
        xL++;
        
        usleep(80000);
    }
    mvwaddch(this->map->getWin(), this->yLoc, xL-1, ' ');
    wrefresh(this->map->getWin());

    yx c;
    c.x = xL+1;
    c.y = yLoc;

    return c;
}

yx Enemy::shoot_top_3(){
    int yL = this->yLoc-1;

    while(map->is_blank(yL-1, xLoc)){
        if(yL != yLoc-1) mvwaddch(this->map->getWin(), yL+1, this->xLoc, ' ');
        mvwaddch(this->map->getWin(), yL, this->xLoc, '|');
        wrefresh(this->map->getWin());
        yL--;
        
        usleep(80000);
    }
    mvwaddch(this->map->getWin(), yL+1, this->xLoc, ' ');
    wrefresh(this->map->getWin());

    yx c;
    c.x = this->xLoc;
    c.y = yL-1;

    return c;
}

yx Enemy::shoot_down_3(){
    int yL = this->yLoc+1;

    while(map->is_blank(yL+1, xLoc)){
        if(yL != yLoc+1) mvwaddch(this->map->getWin(), yL-1, this->xLoc, ' ');
        mvwaddch(this->map->getWin(), yL, this->xLoc, '|');
        wrefresh(this->map->getWin());
        yL++;
        
        usleep(80000);
    }
    mvwaddch(this->map->getWin(), yL-1, this->xLoc, ' ');
    wrefresh(this->map->getWin());

    yx c;
    c.x = this->xLoc;
    c.y = yL+1;

    return c;
}

yx Enemy::shoot_3(){
    yx c;

    srand(time(NULL));
    int n = rand() % 4;

    if(n == 0) c = shoot_top_3();
    else if(n == 1) c = shoot_down_3();
    else if(n == 2) c = shoot_left_3();
    else if(n == 3) c = shoot_right_3();

    return c;
}

yx Enemy::shoot_1(){
    int xL = this->xLoc-1;

    if(!(yLoc == p->get_yLoc() && xLoc != p->get_xLoc()-1)){
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
    }
    
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
    } 
    else{
        mvwaddch(map->getWin(), yLoc, xLoc, '*');
        wrefresh(map->getWin());
        usleep(500000);
        mvwaddch(map->getWin(), yLoc, xLoc, this->ch);
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
    else if(this->type == 3) return shoot_3();
    else return shoot_4();
}

void Enemy::mv(){
    if(type == 1) mv_1();
    else if(type == 2) mv_2();
    else if(type == 3) mv_3();
    else if(type == 4) mv_4();
}

int Enemy::get_type(){
    return this->type;
}

bool Enemy::is_occupied(int y, int x){
    if(mvwinch(map->getWin(), y, x) == '@') return true;
    if(mvwinch(map->getWin(), y, x) == '!') return true;
    if(mvwinch(map->getWin(), y, x) == '?') return true;
    if(mvwinch(map->getWin(), y, x) == '#') return true;
    if(mvwinch(map->getWin(), y, x) == '&') return true;
    if(mvwinch(map->getWin(), y, x) == '*') return true;
    else return false;
}