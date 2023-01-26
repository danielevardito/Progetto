#ifndef _SUB_WIN_HPP_
#define _SUB_WIN_HPP_

#include <ncurses.h>

using namespace std;

/*
Classe che rappresenta una sottofinestra. Essa serve alle varie sottofinestre
che hanno attributi e metodi in comune.
*/
class SubWin{
    protected:
      WINDOW *win;
    public:
      SubWin(int height, int width, int y0, int x0);

      int get_beg_x();
      int get_beg_y();
      int get_width();
      int get_height();
      void draw_empty();

};

#endif