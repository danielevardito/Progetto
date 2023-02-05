#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <unistd.h>
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
      int weapon;
      int last_pressed_x = 0;

      int lives = 5;
      int coins = 0;

    public:
      Player(MainWin *mw, Map *map, int weapon);

      void new_game(Map *map, int weapon);
      StatsWin* get_stats_win();

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

      void shoot_1(int speed);
      void shoot_2(int speed);
      void shoot_3(int speed);
};

#endif