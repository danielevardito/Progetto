#include "PlayMenu.hpp"

using namespace std;

PlayMenu::PlayMenu(MainWin *mw) : SubWin(mw, 2){
    SubWin(mw, 0);
    box(win, 0, 0);
}
/*
Visualizza il menu, al valore di ritorno 0 è associato play, quindi comincerà una partita, 
al valore di ritorno 1 è associato quit, quindi il gioco terminerà.
*/
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
    mvwchgat(this->win, this->get_height()/2-1, this->get_width()/2-2, 1, A_STANDOUT, 1, NULL);

    keypad(this->win, true);
    char c;
    //while che non si ferma finchè non venga fatta una scelta dall'utente e quindi is_pressed cambi valore
    while((c = wgetch(this->win)) && this->is_pressed == -1){
        if((c == (char)KEY_UP) || (c == (char)KEY_DOWN)) {
            //se era evidenziato PLAY evidenzia QUIT, nel caso contrario viceversa
            if(button == 0){
                mvwchgat(this->win, this->get_height()/2-1, this->get_width()/2-2, 1, A_NORMAL, 1, NULL);
                mvwchgat(this->win, this->get_height()/2+1, this->get_width()/2-2, 1, A_STANDOUT, 1, NULL);
                button = 1;
            }
            else{
                mvwchgat(this->win, this->get_height()/2-1, this->get_width()/2-2, 1, A_STANDOUT, 1, NULL);
                mvwchgat(this->win, this->get_height()/2+1, this->get_width()/2-2, 1, A_NORMAL, 1, NULL);
                button = 0;
            }
        }   
        //nel caso in cui venga premuta barra spaziatrice, seleziona play o quit
        else if(int(c) == ' '){
            this->is_pressed = button;
        }
    }

    return this->is_pressed;
    
}

