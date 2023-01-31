#include <ncurses.h>
#include "Map.hpp"

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

    public:
      Player(Map *map);
      void mvup();
      void mvdown();
      void mvleft();
      void mvright();

      int getmv();
      void display();
};