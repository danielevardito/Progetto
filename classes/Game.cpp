#include "Game.hpp"

Game::Game(Player *pl, Map *map, StatsWin *sw){
    pl = new Player(map, sw);
}