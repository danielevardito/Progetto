#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <time.h> 
#include <stdlib.h>
#include "SubWin.hpp"

class Map : public SubWin{
    public:
      Map(int height, int width, int y0, int x0);
      void draw_map1();
      WINDOW* getWin();
};

#endif