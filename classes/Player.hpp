#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <unistd.h>
#include <ncurses.h>
#include "Map.hpp"
#include "StatsWin.hpp"

using namespace std;

struct yx{
  int y;
  int x;
};

class Player{
    protected:
      //punto della mappa in cui si trova il player
      int xLoc;
      int yLoc;
      int xMax;
      int yMax;
      //carattere che rappresenta il player
      char ch;
      char leftChar;
      //mappa in cui si gioca attualmente e finestra delle statistiche
      Map *map;
      StatsWin *sw;
      //arma che sta usando il player correntemente
      int weapon;
      //velocità dell'arma che sta usando il player correntemente
      int w_speed;
      //variabile che serve a decidere da che parte sparare
      int last_pressed_x = 0;

      //vite e soldi del player
      int lives = 5;
      int coins = 0;

      void mvup();
      void mvdown();
      void mvleft();
      void mvright();

      yx shoot_1();
      yx shoot_2();
      yx shoot_3();

    public:
      Player(MainWin *mw, Map *map);

      void new_game(Map *map, int weapon, int w_speed);
      StatsWin* get_stats_win();

      int getmv();
      void display();

      void decrease_lives();
      void reset_lives();
      void increase_coins(int coins);
      bool decrease_coins(int coins);

      int get_coins();
      int get_lives();
      int get_weapon();
      int get_w_speed();
      int get_yLoc();
      int get_xLoc();

      yx shoot();

      bool hitted(int y, int x);
};

#endif