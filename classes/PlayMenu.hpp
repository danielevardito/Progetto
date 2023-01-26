#ifndef _PLAY_MENU_HPP
#define _PLAY_MENU_HPP

#include "SubWin.hpp"

class PlayMenu : public SubWin{
    protected:
      int is_pressed = -1;
    public:
      PlayMenu(int height, int width, int y0, int x0);
      int menu();
      int getPressed();
};

#endif