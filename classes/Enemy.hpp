#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "Player.hpp"

class Enemy{
    protected:
      Map *map;
      Player *p;
      int xLoc;
      int yLoc;
      int xMax;
      int yMax;
      char ch;
      char leftChar;
      int weapon;
      int type;
      int last_move_x = 0;
    public:
      Enemy(Map *map, Player *p, int type, int yLoc);
      void display();
      void mvup_1(int nY);
      void mvdown_1(int nY);
      void mvleft_1(int nX);
      void mvright_1(int nX);
      yx shoot_1();
      void mv_1();
};

#endif