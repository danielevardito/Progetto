#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "Map.hpp"

class Enemy{
    protected:
      Map *map;
      int xLoc;
      int yLoc;
      int xMax;
      int yMax;
      char ch;
      char leftChar;
      int weapon;
      int last_move_x = 0;
    public:
      Enemy(Map *map, int type);
};

#endif