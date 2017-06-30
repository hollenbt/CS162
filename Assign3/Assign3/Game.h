#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "World.h"

class Game {
        World w;
        string username;
        double gold_invested;

        void menu();
        void buy_creatures();
        void add_money();
        void start_tournament();
        void summarize() const;

    public:
        Game();
        void play();
};

#endif // GAME_H_INCLUDED
