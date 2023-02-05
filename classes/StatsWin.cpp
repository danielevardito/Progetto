#include "StatsWin.hpp"

StatsWin::StatsWin(MainWin *mw) : SubWin(mw, false){
    SubWin(mw, false);
    wrefresh(this->win);
}

void StatsWin::display(int l, int c){
    this->draw_empty();

    string lives = "LIVES: ";
    lives += to_string(l);
    mvwprintw(this->win, 1, 1, lives.c_str());

    string coins = "COINS: ";
    coins += to_string(c);
    mvwprintw(this->win, 1, 3 + lives.length(), coins.c_str());

    box(this->win, 0, 0);

    wrefresh(this->win);
}