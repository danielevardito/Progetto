#ifndef _GAME_HPP_
#define _GAME_HPP_

#define L 100

#include <ncurses.h>
#include "Player.hpp"
#include "Enemy.hpp"

struct player_prop{
  int weapon;
  int w_speed;
  int lives;
  int coins;
};

struct game_prop{
  player_prop pp;
  map_prop mp;
  int won = 0;
};

struct b_list{
    game_prop gp;
    b_list *next;
    b_list *prev;
};
typedef b_list* p_b_list;

using namespace std;

/*
classe che si occupa di gestire una partita, giocata in una determinata mappa con un giocatore
che ha determinate proprietà (es. soldi, vita, armi) 
*/
class Game{
    protected:
      Player *p;
      Map *map;
      StatsWin *sw;
      Enemy *enemies[100];
      int intervals[100];
      int nEnemies;

      game_prop gp;
      int prev;

      void select_diff();
    public:
      Game(MainWin *mw, Map *map, Player *p, p_b_list list, int prev);
      //Funzione che fa giocare una partita e ne restituisce l'esito
      bool all_dead(int i);
      game_prop play_game();
};

#endif