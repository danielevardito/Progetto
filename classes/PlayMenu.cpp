#include "PlayMenu.hpp"

using namespace std;

PlayMenu::PlayMenu(int height, int width, int y0, int x0) : SubWin(height, width, y0, x0){
    SubWin(height, width, y0, x0);
}

void PlayMenu::draw_menu(){
    mvwprintw(this->win, this->get_height()/2-1, this->get_width()/2-2, "PLAY");
    mvwprintw(this->win, this->get_height()/2+1, this->get_width()/2-2, "QUIT");

    int button = 0;
    mvwchgat(this->win, this->get_height()/2-1, this->get_width()/2-2, 4, A_STANDOUT, 1, NULL);

    keypad(this->win, true);
    char c;
    while((c = wgetch(this->win)) && this->is_pressed == -1){
        if((c == (char)KEY_UP) || (c == (char)KEY_DOWN)) {
            if(button == 0){
                mvwchgat(this->win, this->get_height()/2-1, this->get_width()/2-2, 4, A_NORMAL, 1, NULL);
                mvwchgat(this->win, this->get_height()/2+1, this->get_width()/2-2, 4, A_STANDOUT, 1, NULL);
                button = 1;
            }
            else{
                mvwchgat(this->win, this->get_height()/2-1, this->get_width()/2-2, 4, A_STANDOUT, 1, NULL);
                mvwchgat(this->win, this->get_height()/2+1, this->get_width()/2-2, 4, A_NORMAL, 1, NULL);
                button = 0;
            }
        }   
        else{
            this->is_pressed = button;
        }
        wrefresh(this->win);
    }
    
}

