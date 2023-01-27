#include "Map.hpp"

Map::Map(int height, int width, int y0, int x0) : SubWin(height, width, y0, x0){
    srand (time(NULL));
    SubWin(height, width, y0, x0);
}

void Map::draw_spaces(){
    for(int i = 0; i < 3; i++){
        mvwhline(this->win, this->get_height()/2+i, 0, ' ', 3);
    }
    
    for(int i = 0; i < 3; i++){
        mvwhline(this->win, 0, this->get_width()-4, ' ', 4);
    }

    mvwhline(this->win, this->get_height()/2, 0, ' ', this->get_width());
}

void Map::draw_map1(){
    int n;
    int nX = rand() % this->get_width()/10 + 2;
    int i;

    for(i = 1; i < nX; i = i+2){
        
        n = rand() % (this->get_height()/2) +1;
        n = this->get_height()-n;
        mvwvline(this->win, n, this->get_width()/nX*i, ACS_VLINE, n);
    
        n = rand() % (this->get_height()/2) +1;
        mvwvline(this->win, 0, this->get_width()/nX*(i+1), ACS_VLINE, n);

    }

    this->draw_spaces();

    wrefresh(this->win);
}

void Map::draw_map2(){
    int n = rand() % 6+3;
    int x0, y0, nX, nY;

    for(int i = 0; i < n; i++){
        x0 = rand() % this->get_width();
        y0 = rand() % this->get_height();

        nX = rand() % 5+1;
        nY = rand() % 4+1;

        for(int j = y0; j < nY+y0; j++){
            mvwhline(this->win, j, x0, 'X', nX);
        }
    }

    this->draw_spaces();

    wrefresh(this->win);
}

void Map::draw_map4(){
    int height7 = this->get_height()/7;
    int width10 = this->get_width()/10;
    mvwhline(this->win, height7*3, 0, ACS_HLINE, width10);
    mvwhline(this->win, height7*5, 0, ACS_HLINE, width10*2);
    mvwvline(this->win, height7, width10, ACS_VLINE, height7*2);
    mvwaddch(this->win, height7*3, width10, ACS_LRCORNER);
    mvwvline(this->win, height7*2, width10*2, ACS_VLINE, height7*3);
    mvwaddch(this->win, height7*5, width10*2, ACS_LRCORNER);
    mvwhline(this->win, height7, width10, ACS_HLINE, width10*8);
    mvwaddch(this->win, height7, width10, ACS_ULCORNER);
    mvwvline(this->win, 0, width10*9, ACS_VLINE, height7);
    mvwaddch(this->win, height7, width10*9, ACS_LRCORNER);
    mvwhline(this->win, height7*2, width10*2, ACS_HLINE, width10);
    mvwaddch(this->win, height7*2, width10*2, ACS_ULCORNER);
    mvwvline(this->win, height7*2, width10*3, ACS_VLINE, height7*4);
    mvwaddch(this->win, height7*2, width10*3, ACS_URCORNER);
    mvwhline(this->win, height7*6, width10*3, ACS_HLINE, width10*3);
    mvwaddch(this->win, height7*6, width10*3, ACS_LLCORNER);
    mvwvline(this->win, height7*5, width10*6, ACS_VLINE, height7);
    mvwaddch(this->win, height7*6, width10*6, ACS_LRCORNER);
    mvwhline(this->win, height7*5, width10*6, ACS_HLINE, width10);
    mvwaddch(this->win, height7*5, width10*6, ACS_ULCORNER);
    mvwvline(this->win, height7*5, width10*7, ACS_VLINE, height7);
    mvwaddch(this->win, height7*5, width10*7, ACS_URCORNER);
    mvwhline(this->win, height7*6, width10*7, ACS_HLINE, width10*2);
    mvwaddch(this->win, height7*6, width10*7, ACS_LLCORNER);
    mvwvline(this->win, height7*6, width10*9, ACS_VLINE, height7*2);
    mvwaddch(this->win, height7*6, width10*9, ACS_URCORNER);
    mvwhline(this->win, height7*2, width10*4, ACS_HLINE, width10*3);
    mvwvline(this->win, height7*2, width10*4, ACS_VLINE, height7);
    mvwvline(this->win, height7*2, width10*7, ACS_VLINE, height7);
    mvwaddch(this->win, height7*2, width10*4, ACS_ULCORNER);
    mvwaddch(this->win, height7*2, width10*7, ACS_URCORNER);
    mvwhline(this->win, height7*3, width10*4, ACS_HLINE, width10*2);
    mvwvline(this->win, height7*3, width10*6, ACS_VLINE, height7);
    mvwaddch(this->win, height7*3, width10*4, ACS_LLCORNER);
    mvwaddch(this->win, height7*3, width10*6, ACS_URCORNER);

    wrefresh(this->win);
}

WINDOW* Map::getWin(){
    return this->win;
}