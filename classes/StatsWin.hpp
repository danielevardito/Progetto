#ifndef _STATS_WIN_HPP_
#define _STATS_WIN_HPP_

#include "SubWin.hpp"
#include <string>

class StatsWin : public SubWin{
    public:
      StatsWin(MainWin *mw);
      void display(int l, int c);
};

#endif