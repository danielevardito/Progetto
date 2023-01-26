#include "MainWin.hpp"

MainWin::MainWin(){
    int xMax, yMax, y0, x0, height, width;
    getmaxyx(stdscr, yMax, xMax);
    height = yMax / 20 * 18;
    width = xMax / 20 * 18;
    y0 = yMax / 20;
    x0 = xMax / 20;

    this->win = newwin(height, width, y0, x0);
}

int MainWin::get_beg_x(){
    return getbegx(this->win);
}

int MainWin::get_beg_y(){
    return getbegy(this->win);
}

int MainWin::get_height(){
    return getmaxy(this->win);
}

int MainWin::get_width(){
    return getmaxx(this->win);
}

void MainWin::draw_empty(){
    box(this->win, 0, 0);
    refresh();
    wrefresh(this->win);
}
