#include "PlayMenu.hpp"

using namespace std;

PlayMenu::PlayMenu(int height, int width, int y0, int x0) : SubWin(height, width, y0, x0){
    SubWin(height, width, y0, x0);
}

int PlayMenu::menu(){
    //setta la variabile che sarà ritornata a -1 per indicare che non c'è stata ancora nessuna scelta
    //da parte dell'utente
    this->is_pressed = -1;

    //scrivo i bottoni PLAY e QUIT, 
    mvwprintw(this->win, this->get_height()/2-1, this->get_width()/2-2, "PLAY");
    mvwprintw(this->win, this->get_height()/2+1, this->get_width()/2-2, "QUIT");

    //setto a 0 il button, quindi evidenzio PLAY. Button contiene l'indice del bottone correntemente
    //evidenziato
    int button = 0; 
    mvwchgat(this->win, this->get_height()/2-1, this->get_width()/2-2, 4, A_STANDOUT, 1, NULL);

    keypad(this->win, true);
    char c;
    //while che non si ferma finchè non venga fatta una scelta dall'utente e quindi is_pressed cambi valore
    while((c = wgetch(this->win)) && this->is_pressed == -1){
        if((c == (char)KEY_UP) || (c == (char)KEY_DOWN)) {
            //se era evidenziato PLAY evidenzia QUIT, nel caso contrario viceversa
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
        //nel caso in cui non venga premuta una freccetta, assgna a is_pressed l'indice della voce del menu
        //evidenziata correntemente
        else{
            this->is_pressed = button;
        }
    }

    return this->is_pressed;
    
}

