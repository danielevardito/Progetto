#include "SubWin.hpp"

SubWin::SubWin(int height, int width, int y0, int x0){
    this->win = newwin(height-2, width-2, y0+1, x0+1);
    //box(this->win, 0, 0);
}

int SubWin::get_beg_x(){
    return getbegx(this->win);
}

int SubWin::get_beg_y(){
    return getbegy(this->win);
}

int SubWin::get_height(){
    return getmaxy(this->win);
}

int SubWin::get_width(){
    return getmaxx(this->win);
}

void SubWin::draw_empty(){
    wclear(this->win);
    refresh();
    wrefresh(this->win);
}


