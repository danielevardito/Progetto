#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <ncurses.h>
#include "Map.hpp"
#include "StatsWin.hpp"

using namespace std;

class Player{
    protected:
      int xLoc;
      int yLoc;
      int xMax;
      int yMax;
      char ch;
      char leftChar;
      Map *map;
      StatsWin *sw;

      int lives = 5;
      int coins = 0;

    public:
      Player(Map *map, StatsWin *sw);
      void mvup();
      void mvdown();
      void mvleft();
      void mvright();

      int getmv();
      void display();

      void decrease_lives();
      void increase_coins(int coins);
      bool decrease_coins(int coins);

      int get_coins();
      int get_lives();
};

#endif