#ifndef _MAP_HPP_
#define _MAP_HPP_

#define L1 100

#include "SubWin.hpp"

struct rand1{
    int nX = 0;
    int l1[L1];
    int l2[L1];
};

struct rand2{
    int n = 0;
    int y0[L1];
    int x0[L1];
    int nY[L1];
    int nX[L1];
};

struct map_prop{
    int nMap = rand()%9+1;
    rand1 r1;
    rand2 r2;
};

class Map : public SubWin{
    protected:
      void draw_spaces();
      rand2 draw_mapX();
      void draw_cp_mapX(rand2 r2);
    public:
      Map(MainWin *mw);
      rand1 draw_map1();
      void draw_cp_map1(rand1 r1);
      map_prop draw_map2();
      void draw_cp_map2(map_prop mp);
      void draw_map3();
      void draw_map4();
      void draw_map5();
      void draw_map6();
      void draw_map7();
      void draw_map8();
      void draw_map9();
      map_prop draw_n_map(int n);
      void draw_n_cp_map(map_prop mp);

      void draw_market(int weapon);

      bool is_blank(int y, int x);
      WINDOW* getWin();
};

#endif