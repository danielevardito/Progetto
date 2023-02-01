#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <ncurses.h>
#include "Map.hpp"
#include "Player.hpp"

using namespace std;

class Game{
    protected:
      StatsWin *sw;
    public:
      Game(Player *pl, Map *map, StatsWin *sw);
      bool play_game();
};

#endif