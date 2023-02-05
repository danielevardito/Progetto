#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <ncurses.h>
#include "Player.hpp"
#include "Enemy.hpp"

using namespace std;

class Game{
    protected:
      Player *p;
      Map *map;
      StatsWin *sw;
    public:
      Game(MainWin *mw, Map *map, Player *p);
      bool play_game();
};

#endif