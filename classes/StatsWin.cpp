#include "StatsWin.hpp"

StatsWin::StatsWin(MainWin *mw) : SubWin(mw, false){
    SubWin(mw, false);
    wrefresh(this->win);
}

void StatsWin::display(int l, int c){
    this->draw_empty();

    string lives = "LIVES: ";
    lives += l;
    mvwprintw(this->win, this->get_height()/2 - 1, this->get_width()-lives.length()/2, lives.c_str());

    string coins = "COINS: ";
    coins += c;
    mvwprintw(this->win, this->get_height()/2 + 1, this->get_width()-coins.length()/2, coins.c_str());

    wrefresh(this->win);
}