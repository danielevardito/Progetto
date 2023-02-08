#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "Player.hpp"

class Enemy{
    protected:
      Map *map;
      Player *p;
      int xLoc;
      int yLoc;
      int xMax;
      int yMax;
      char ch;
      char leftChar;
      int weapon;
      int type;
      int lives;
      int last_move_x = 0;

      void mvup_1(int nY);
      void mvdown_1(int nY);
      void mvleft_1(int nX);
      void mvright_1(int nX);
      yx shoot_1();
      void mv_1();

      void mvup_2(int nY);
      void mvdown_2(int nY);
      void mvleft_2(int nX);
      void mvright_2(int nX);
      yx shoot_2();
      void mv_2();

      void mvup_3(int i);
      void mvdown_3(int i);
      void mvleft_3(int i);
      void mvright_3(int i);

      yx shoot_left_3();
      yx shoot_right_3();
      yx shoot_top_3();
      yx shoot_down_3();
      yx shoot_3();
      void mv_3();

      yx shoot_4();
      void mv_4();

      bool is_occupied(int y, int x);
    public:
      Enemy(Map *map, Player *p, int type, int yLoc);
      void display();
      
      yx shoot();
      void mv();

      int get_yLoc();
      int get_xLoc();
      int get_lives();

      int get_type();

      void decrease_lives();
      bool dead();

};

#endif