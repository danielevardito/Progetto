#include "StatsWin.hpp"

StatsWin::StatsWin(MainWin *mw) : SubWin(mw, 0){
    SubWin(mw, false);
    wrefresh(this->win);
}
/*
mostra le statistiche del Player.
Esse sono vite, soldi, tipo di arma, velocità dell'arma
*/
void StatsWin::display(int l, int c, int w, int s_w){
    this->draw_empty();

    string lives = "LIVES: ";
    lives += to_string(l);
    mvwprintw(this->win, 1, 1, lives.c_str());

    string coins = "COINS: ";
    coins += to_string(c);
    mvwprintw(this->win, 1, 3 + lives.length(), coins.c_str());

    string weapon = "WEAPON: ";
    if(w == 1) weapon += ">";
    else if(w == 2) weapon += "|";
    else if(w == 3) weapon += "Z";

    mvwprintw(this->win, 1, 6 + coins.length() + lives.length(), weapon.c_str());

    string speed = "WEAPON SPEED: ";
    speed += to_string(s_w);
    mvwprintw(this->win, 1, 9 + coins.length() + lives.length() + weapon.length(), speed.c_str());

    box(this->win, 0, 0);

    wrefresh(this->win);
}