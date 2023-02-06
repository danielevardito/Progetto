#ifndef _GAME_HPP_
#define _GAME_HPP_

#define L 100

#include <ncurses.h>
#include "Player.hpp"
#include "Enemy.hpp"

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
    public:
      Game(MainWin *mw, Map *map, Player *p);
      //Funzione che fa giocare una partita e ne restituisce l'esito
      bool all_dead(int i);
      int play_game();
      int enemies_size();
};

#endif