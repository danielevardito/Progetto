#include "Map.hpp"

Map::Map(int height, int width, int y0, int x0) : SubWin(height, width, y0, x0){
    srand (time(NULL));
    SubWin(height, width, y0, x0);
}

void Map::draw_map1(){
    int n;
    int nX = rand() % this->get_width()/4 + 3;
    int j;

    for(j = 1; j < nX; j = j+2){
        n = rand() % (this->get_height()/2) +1;
        n = this->get_height()-n;
        for(int i = this->get_height(); i >= n; i--){
        mvwprintw(this->win, i, this->get_width()/nX*j, "│");
        }
    
        n = rand() % (this->get_height()/2) +1;
        for(int i = 0; i <= n; i++){
            mvwprintw(this->win, i, this->get_width()/nX*(j+1), "│");
        }
    }

    wrefresh(this->win);
}

WINDOW* Map::getWin(){
    return this->win;
}