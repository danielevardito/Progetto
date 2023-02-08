#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <time.h> 
#include <stdlib.h>
#include "SubWin.hpp"

class Map : public SubWin{
    protected:
      void draw_spaces();
      void draw_mapX();
    public:
      Map(MainWin *mw);
      void draw_map1();
      void draw_map2();
      void draw_map3();
      void draw_map4();
      void draw_map5();
      void draw_n_map(int n);

      void draw_market(int weapon);

      bool is_blank(int y, int x);
      WINDOW* getWin();
};

#endif