#ifndef _MAIN_WIN_HPP_
#define _MAIN_WIN_HPP_

#include <ncurses.h>
#include <string>

using namespace std;

/*
Classe che rappresenta la finestra contenente tutte le altre finestre.
Essa è responsabile di switchare tra le varie finestre (interne) che
 rappresentano i vari stati del gioco. 
*/
class MainWin{
    protected:
      WINDOW *win;
    public:
      MainWin(); //inizializza la finestra
      int get_beg_x();
      int get_beg_y();
      int get_width();
      int get_height();
      void draw_empty();
};

#endif