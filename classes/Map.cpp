#include "Map.hpp"

Map::Map(int height, int width, int y0, int x0) : SubWin(height, width, y0, x0){
    srand (time(NULL));
    SubWin(height, width, y0, x0);
}
/*
Scrive degli spazi al centro e ai lati della mappa per fare in modo che il personaggio e i nemici
si possano sempre incontrare
*/
void Map::draw_spaces(){
    mvwvline(this->win, 0, 0, ' ', this->get_height());
    mvwvline(this->win, 0, 1, ' ', this->get_height());

    mvwvline(this->win, 0, this->get_width()-1, ' ', this->get_height());
    mvwvline(this->win, 0, this->get_width()-2, ' ', this->get_height());

    mvwhline(this->win, this->get_height()/2, 0, ' ', this->get_width());
}
/*
Prima mappa, genera n linee di m lunghezza, dove n e m sono randomici.
*/
void Map::draw_map1(){
    this->draw_empty();

    int n;
    int nX = rand() % this->get_width()/7 + 6;
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
/*
È una pseudo mappa randomica che serve a creare la mappa 2. Essa è composta da n rettangoli di 
h e b dimensioni, dove h e b sono generati randomicamente.
*/
void Map::draw_mapX(){
    box(this->win, 'X', 'X');

    int n = rand() % 6+5;
    int x0, y0, nX, nY;

    for(int i = 0; i < n; i++){
        x0 = rand() % this->get_width();
        y0 = rand() % this->get_height();

        nX = rand() % 3+3;
        nY = rand() % 3+3;

        for(int j = y0; j < nY+y0; j++){
            mvwhline(this->win, j, x0, 'X', nX);
        }
    }

    this->draw_spaces();

    wrefresh(this->win);
}
/*
È una combinazione tra mappa1 e mappaX, quindi ci saranno n rettangoli e m linee generati randomicamente 
*/
void Map::draw_map2(){
    this->draw_empty();

    this->draw_map1();
    this->draw_mapX();
}
/*
Prima mappa disegnata, è fatta con unità basate in frazioni di 7 per l'altezza e 
frazioni di 10 per la lunghezza.
*/
void Map::draw_map3(){
    this->draw_empty();

    double height7 = this->get_height()/7;
    double width10 = this->get_width()/10;
    mvwhline(this->win, height7*3, 0, ACS_HLINE, width10);
    mvwvline(this->win, height7*5, width10, ACS_VLINE, height7*5);
    mvwhline(this->win, height7*5, width10, ACS_HLINE, width10);
    mvwaddch(this->win, height7*5, width10, ACS_ULCORNER);
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
    mvwvline(this->win, height7*6, width10*9, ACS_VLINE, height7*4);
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

/*
Seconda mappa disegnata. È fatta con unità basate in frazioni di 7 per l'altezza e frazioni di 12
per la lunghezza
*/
void Map::draw_map4(){
    this->draw_empty();

    int heigth7 = this->get_height()/7;
    int width12 = this->get_width()/12;

    mvwvline(win, 0, width12, ACS_VLINE, heigth7*3);
    mvwvline(win, heigth7*5, width12, ACS_VLINE, heigth7*5);
    mvwvline(win, heigth7, width12*2, ACS_VLINE, heigth7*4);
    mvwhline(win, heigth7*5, width12, ACS_HLINE, width12);
    mvwhline(win, 0, width12, ACS_HLINE, width12*3);
    mvwaddch(win, heigth7*5, width12, ACS_ULCORNER);
    mvwaddch(win, heigth7*5, width12*2, ACS_LRCORNER);
    mvwaddch(win, 0, width12, ACS_ULCORNER);
    mvwhline(win, heigth7, width12*2, ACS_HLINE, width12);
    mvwvline(win, heigth7, width12*3, ACS_VLINE, heigth7*3);
    mvwaddch(win, heigth7, width12*2, ACS_ULCORNER);
    mvwaddch(win, heigth7, width12*3, ACS_URCORNER);
    mvwvline(win, 0, width12*4, ACS_VLINE, heigth7*2);
    mvwaddch(win, 0, width12*4, ACS_URCORNER);
    mvwhline(win, heigth7*4, width12*3, ACS_HLINE, width12*2);
    mvwvline(win, heigth7*3, width12*5, ACS_VLINE, heigth7);
    mvwhline(win, heigth7*3, width12*5, ACS_HLINE, width12);
    mvwhline(win, heigth7*2, width12*4, ACS_HLINE, width12*5);
    mvwaddch(win, heigth7*4, width12*3, ACS_LLCORNER);
    mvwaddch(win, heigth7*4, width12*5, ACS_LRCORNER);
    mvwaddch(win, heigth7*3, width12*5, ACS_ULCORNER);
    mvwaddch(win, heigth7*2, width12*4, ACS_LLCORNER);
    mvwvline(win, heigth7*3, width12*6, ACS_VLINE, heigth7*3);
    mvwvline(win, heigth7*2, width12*9, ACS_VLINE, heigth7*3);
    mvwaddch(win, heigth7*3, width12*6, ACS_URCORNER);
    mvwaddch(win, heigth7*2, width12*9, ACS_URCORNER);
    mvwhline(win, heigth7*5, width12*9, ACS_HLINE, width12*3);
    mvwhline(win, heigth7*6, width12*6, ACS_HLINE, width12*6);
    mvwaddch(win, heigth7*6, width12*6, ACS_LLCORNER);
    mvwaddch(win, heigth7*5, width12*9, ACS_LLCORNER);
    mvwvline(win, 0, width12*12, ACS_VLINE, heigth7*5);
    mvwvline(win, heigth7*6, width12*12, ACS_VLINE, heigth7*3);
    mvwaddch(win, heigth7*5, width12*12, ACS_LRCORNER);
    mvwaddch(win, heigth7*6, width12*12, ACS_URCORNER);

    wrefresh(win);
}
/*
Terza mappa disegnata. È fatta con unità basate in frazioni di 7 per l'altezza e frazioni di 12
per la lunghezza.
*/
void Map::draw_map5(){
    this->draw_empty();

    int heigth7 = this->get_height()/7;
    int width12 = this->get_width()/12;

    mvwvline(win, heigth7*2, width12, ACS_VLINE, heigth7*2);
    mvwvline(win, heigth7*5, width12, ACS_VLINE, heigth7*2);
    mvwhline(win, heigth7*2, width12, ACS_HLINE, width12*4);
    mvwhline(win, heigth7*7, width12, ACS_HLINE, width12*4);
    mvwaddch(win, heigth7*2, width12, ACS_ULCORNER);
    mvwaddch(win, heigth7*7, width12, ACS_LLCORNER);

    mvwvline(win, heigth7*3, width12*2, ACS_VLINE, heigth7);
    mvwvline(win, heigth7*5, width12*2, ACS_VLINE, heigth7);
    mvwhline(win, heigth7*3, width12*2, ACS_HLINE, width12*3);
    mvwhline(win, heigth7*6, width12*2, ACS_HLINE, width12*3);
    mvwaddch(win, heigth7*3, width12*2, ACS_ULCORNER);
    mvwaddch(win, heigth7*6, width12*2, ACS_LLCORNER);

    mvwvline(win, heigth7*2, width12*12, ACS_VLINE, heigth7*2);
    mvwvline(win, heigth7*5, width12*12, ACS_VLINE, heigth7*2);
    mvwhline(win, heigth7*2, width12*7, ACS_HLINE, width12*5);
    mvwhline(win, heigth7*7, width12*7, ACS_HLINE, width12*5);
    mvwaddch(win, heigth7*2, width12*12, ACS_URCORNER);
    mvwaddch(win, heigth7*7, width12*12, ACS_LRCORNER);

    mvwvline(win, heigth7*3, width12*11, ACS_VLINE, heigth7);
    mvwvline(win, heigth7*5, width12*11, ACS_VLINE, heigth7);
    mvwhline(win, heigth7*3, width12*7, ACS_HLINE, width12*4);
    mvwhline(win, heigth7*6, width12*7, ACS_HLINE, width12*4);
    mvwaddch(win, heigth7*3, width12*11, ACS_URCORNER);
    mvwaddch(win, heigth7*6, width12*11, ACS_LRCORNER);

    wrefresh(win);
}

/*
Dato un numero, disegna la mappa corrispondente. 
*/
void Map::draw_n_map(int n){
    switch(n){
        case 1:
          this->draw_map1();
          break;

        case 2:
          this->draw_map2();
          break;

        case 3:
          this->draw_map3();
          break;

        case 4:
          this->draw_map4();
          break;

        case 5:
          this->draw_map5();
          break;

        default:
          this->draw_map2();
          break;
    }
}

bool Map::is_blank(int y, int x){
    if(mvwinch(this->win, y, x) == ' ') return true;
    else return false;
}

WINDOW* Map::getWin(){
    return this->win;
}