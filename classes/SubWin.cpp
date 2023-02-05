#include "SubWin.hpp"

SubWin::SubWin(MainWin *mw, bool wide){
    if(wide) 
      this->win = newwin(mw->get_height()-3, mw->get_width(), mw->get_beg_y()+2, mw->get_beg_x());
    else
        this->win = newwin(3, mw->get_width(), mw->get_beg_y(), mw->get_beg_x());
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


