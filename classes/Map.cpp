#include "Map.hpp"

Map::Map(MainWin *mw) : SubWin(mw, 1){
    srand (time(NULL));
    SubWin(mw, true);
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
rand1 Map::draw_map1(){
    this->draw_empty();

    int l1, l2;
    int nX = rand() % this->get_width()/4 + 7;
    int i;

    rand1 r1;
    r1.nX = nX;

    for(i = 1; i < nX; i = i+2){
        
        l1 = rand() % (this->get_height()/2) +1;
        r1.l1[i] = l1 = this->get_height()-l1;
        mvwvline(this->win, l1, this->get_width()/nX*i, ACS_VLINE, l1);
    
        r1.l2[i] = l2 = rand() % (this->get_height()/2) +1;
        mvwvline(this->win, 0, this->get_width()/nX*(i+1), ACS_VLINE, l2);

    }

    this->draw_spaces();

    box(this->win, 0, 0);

    wrefresh(this->win);


    return r1;
}

void Map::draw_cp_map1(rand1 r1){
    this->draw_empty();
    int i;

    for(i = 1; i < r1.nX; i = i+2){
        
        mvwvline(this->win, r1.l1[i], this->get_width()/r1.nX*i, ACS_VLINE, r1.l1[i]);
    
        mvwvline(this->win, 0, this->get_width()/r1.nX*(i+1), ACS_VLINE, r1.l2[i]);
    }

    this->draw_spaces();

    box(this->win, 0, 0);

    wrefresh(this->win);
}
/*
È una pseudo mappa randomica che serve a creare la mappa 2. Essa è composta da n rettangoli di 
h e b dimensioni, dove h e b sono generati randomicamente.
*/
rand2 Map::draw_mapX(){
    box(this->win, 'X', 'X');

    rand2 r2;

    int n = rand() % 6+10;
    int x0, y0, nX, nY;

    r2.n = n;

    for(int i = 0; i < n; i++){
        r2.x0[i] = x0 = rand() % this->get_width();
        r2.y0[i] = y0 = rand() % this->get_height();

        r2.nX[i] = nX = rand() % 3+3;
        r2.nY[i] = nY = rand() % 3+3;

        for(int j = y0; j < nY+y0; j++){
            mvwhline(this->win, j, x0, 'X', nX);
        }
    }

    this->draw_spaces();

    wrefresh(this->win);

    return r2;
}

void Map::draw_cp_mapX(rand2 r2){
    box(this->win, 'X', 'X');

    for(int i = 0; i < r2.n; i++){
        for(int j = r2.y0[i]; j < r2.nY[i]+r2.y0[i]; j++){
            mvwhline(this->win, j, r2.x0[i], 'X', r2.nX[i]);
        }
    }

    this->draw_spaces();

    wrefresh(this->win);
}

/*
È una combinazione tra mappa1 e mappaX, quindi ci saranno n rettangoli e m linee generati randomicamente 
*/
map_prop Map::draw_map2(){
 
    this->draw_empty();

    rand1 r1 = this->draw_map1();
    rand2 r2 = this->draw_mapX();

    box(this->win, 0, 0);

    map_prop m;
    m.nMap = 2;
    m.r1 = r1;
    m.r2 = r2;

    return m;
}

void Map::draw_cp_map2(map_prop mp){
    this->draw_empty();

    this->draw_cp_map1(mp.r1);
    this->draw_cp_mapX(mp.r2);

    box(this->win, 0, 0);
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

    box(this->win, 0, 0);

    wrefresh(this->win);
}

/*
Seconda mappa disegnata. È fatta con unità basate in frazioni di 7 per l'altezza e frazioni di 12
per la lunghezza
*/
void Map::draw_map4(){
    this->draw_empty();

    //box(this->win, 0, 0);

    int height7 = this->get_height()/7;
    int width12 = this->get_width()/12;

    mvwvline(win, 0, width12, ACS_VLINE, height7*3);
    mvwvline(win, height7*5, width12, ACS_VLINE, height7*5);
    mvwvline(win, height7, width12*2, ACS_VLINE, height7*4);
    mvwhline(win, height7*5, width12, ACS_HLINE, width12);
    mvwhline(win, 0, width12, ACS_HLINE, width12*3);
    mvwaddch(win, height7*5, width12, ACS_ULCORNER);
    mvwaddch(win, height7*5, width12*2, ACS_LRCORNER);
    mvwaddch(win, 0, width12, ACS_ULCORNER);
    mvwhline(win, height7, width12*2, ACS_HLINE, width12);
    mvwvline(win, height7, width12*3, ACS_VLINE, height7*3);
    mvwaddch(win, height7, width12*2, ACS_ULCORNER);
    mvwaddch(win, height7, width12*3, ACS_URCORNER);
    mvwvline(win, 0, width12*4, ACS_VLINE, height7*2);
    mvwaddch(win, 0, width12*4, ACS_URCORNER);
    mvwhline(win, height7*4, width12*3, ACS_HLINE, width12*2);
    mvwvline(win, height7*3, width12*5, ACS_VLINE, height7);
    mvwhline(win, height7*3, width12*5, ACS_HLINE, width12);
    mvwhline(win, height7*2, width12*4, ACS_HLINE, width12*5);
    mvwaddch(win, height7*4, width12*3, ACS_LLCORNER);
    mvwaddch(win, height7*4, width12*5, ACS_LRCORNER);
    mvwaddch(win, height7*3, width12*5, ACS_ULCORNER);
    mvwaddch(win, height7*2, width12*4, ACS_LLCORNER);
    mvwvline(win, height7*3, width12*6, ACS_VLINE, height7*3);
    mvwvline(win, height7*2, width12*9, ACS_VLINE, height7*3);
    mvwaddch(win, height7*3, width12*6, ACS_URCORNER);
    mvwaddch(win, height7*2, width12*9, ACS_URCORNER);
    mvwhline(win, height7*5, width12*9, ACS_HLINE, width12*2);
    mvwhline(win, height7*6, width12*6, ACS_HLINE, width12*5);
    mvwaddch(win, height7*6, width12*6, ACS_LLCORNER);
    mvwaddch(win, height7*5, width12*9, ACS_LLCORNER);
    mvwvline(win, 0, width12*11, ACS_VLINE, height7*5);
    mvwvline(win, height7*6, width12*11, ACS_VLINE, height7*3);
    mvwaddch(win, height7*5, width12*11, ACS_LRCORNER);
    mvwaddch(win, height7*6, width12*11, ACS_URCORNER);

    box(this->win, 0, 0);

    wrefresh(win);
}
/*
Terza mappa disegnata. È fatta con unità basate in frazioni di 7 per l'altezza e frazioni di 12
per la lunghezza.
*/
void Map::draw_map5(){
    this->draw_empty();

    int height7 = this->get_height()/7;
    int width12 = this->get_width()/12;

    mvwvline(win, height7, width12, ACS_VLINE, height7*2);
    mvwvline(win, height7*4, width12, ACS_VLINE, height7*2);
    mvwhline(win, height7, width12, ACS_HLINE, width12*4);
    mvwhline(win, height7*6, width12, ACS_HLINE, width12*4);
    mvwaddch(win, height7, width12, ACS_ULCORNER);
    mvwaddch(win, height7*6, width12, ACS_LLCORNER);

    mvwvline(win, height7*2, width12*2, ACS_VLINE, height7);
    mvwvline(win, height7*4, width12*2, ACS_VLINE, height7);
    mvwhline(win, height7*2, width12*2, ACS_HLINE, width12*3);
    mvwhline(win, height7*5, width12*2, ACS_HLINE, width12*3);
    mvwaddch(win, height7*2, width12*2, ACS_ULCORNER);
    mvwaddch(win, height7*5, width12*2, ACS_LLCORNER);

    mvwvline(win, height7, width12*10, ACS_VLINE, height7*2);
    mvwvline(win, height7*4, width12*10, ACS_VLINE, height7*2);
    mvwhline(win, height7, width12*6, ACS_HLINE, width12*4);
    mvwhline(win, height7*6, width12*6, ACS_HLINE, width12*4);
    mvwaddch(win, height7, width12*10, ACS_URCORNER);
    mvwaddch(win, height7*6, width12*10, ACS_LRCORNER);

    mvwvline(win, height7*2, width12*9, ACS_VLINE, height7);
    mvwvline(win, height7*4, width12*9, ACS_VLINE, height7);
    mvwhline(win, height7*2, width12*6, ACS_HLINE, width12*3);
    mvwhline(win, height7*5, width12*6, ACS_HLINE, width12*3);
    mvwaddch(win, height7*2, width12*9, ACS_URCORNER);
    mvwaddch(win, height7*5, width12*9, ACS_LRCORNER);

    box(this->win, 0, 0);

    wrefresh(win);
}

void Map::draw_market(int weapon){
    char w, ws;

    if(weapon == 1){
        w = '|';
        ws = '>';
    } 
    else if(weapon == 2){
        w = 'Z';
        ws = '|';
    } 
    else if(weapon == 3){
        w = 'x';
        ws = 'Z';
    } 

    this->draw_empty();

    mvwprintw(win, 1, get_width()/2-3, "MARKET");

    mvwaddch(win, get_beg_y()+2, get_width()/2, w);
    if(weapon == 1) mvwprintw(win, get_beg_y()+2, get_width()/2+2, "   7 COINS: Arma che perfora un muro");
    else if(weapon == 2) mvwprintw(win, get_beg_y()+2, get_width()/2+2, "   7 COINS: Arma che perfora tutti i muri");
    else if(weapon == 3) mvwprintw(win, get_beg_y()+2, get_width()/2+2, "   Hai l'arma più forte");
    mvwaddch(win, get_beg_y()+4, get_width()/2, '+');
    mvwaddch(win, get_beg_y()+4, get_width()/2+1, ws);
    mvwprintw(win, get_beg_y()+4, get_width()/2+3, "   2 COINS: Aumenta la velocità dell'arma");
    mvwaddch(win, get_beg_y()+6, get_width()/2, 'V');
    mvwaddch(win, get_beg_y()+6, get_width()/2+1, '+');
    mvwprintw(win, get_beg_y()+6, get_width()/2+3, "   2 COINS: AUMENTA LA VITA");
    mvwprintw(win, get_height()-2, get_width()/2, "] exit");

    box(this->win, 0, 0);

    wrefresh(win);

}

/*
Dato un numero, disegna la mappa corrispondente. 
*/
map_prop Map::draw_n_map(int n){
    map_prop mp;

    switch(n){
        case 1:
          mp.r1 = draw_map1();
          mp.nMap = 1;
          break;

        case 2:
          mp = draw_map2();
          break;

        case 3:
          draw_map3();
          mp.nMap = 3;
          break;

        case 4:
          this->draw_map4();
          mp.nMap = 4;
          break;

        case 5:
          this->draw_map5();
          mp.nMap = 5;
          break;

        default:
          mp = draw_map2();
          break;
    }
    return mp;

}

void Map::draw_n_cp_map(map_prop mp){
    switch(mp.nMap){
        case 1:
          this->draw_cp_map1(mp.r1);
          break;

        case 2:
          this->draw_cp_map2(mp);
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

/*
Verifica, date le coordinate, se il carattere a x y è vuoto
*/
bool Map::is_blank(int y, int x){
    if(mvwinch(this->win, y, x) == ' ') return true;
    else return false;
}

WINDOW* Map::getWin(){
    return this->win;
}