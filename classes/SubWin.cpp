#include "SubWin.hpp"

/*
Crea la finestra, che può essere di tre tipi, larga, non larga e molto larga.
Con wide = 0 si ha una finestra per le StatsWin
Con wide = 1 si ha una finestra per il market o per la mappa
Con wide = 2 si ha una finestra per play-quit e game over
*/
SubWin::SubWin(MainWin *mw, int wide){
    if(wide == 1) 
      this->win = newwin(mw->get_height()-3, mw->get_width(), mw->get_beg_y()+2, mw->get_beg_x());
    else if(wide == 0)
      this->win = newwin(3, mw->get_width(), mw->get_beg_y(), mw->get_beg_x());
    else if(wide == 2)
      this->win = newwin(mw->get_height()-1, mw->get_width(), mw->get_beg_y(), mw->get_beg_x());
    box(this->win, 0, 0);
      
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


