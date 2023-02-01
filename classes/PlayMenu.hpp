#ifndef _PLAY_MENU_HPP
#define _PLAY_MENU_HPP

#include "SubWin.hpp"

/*
Classe che rappresenta la finestra PLAY-QUIT. Essa eredita proprietà e metodi dalla classe
SubWin, che rappresenta una generica sottofinestra del gioco.
*/

class PlayMenu : public SubWin{
    protected:
      int is_pressed = -1;
    public:
      PlayMenu(MainWin *mw);
      //mostra il menu e restituisce come valore la scelta dell'utente
      int menu(); 
};

#endif