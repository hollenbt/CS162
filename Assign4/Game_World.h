#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "AI.h"

#include "Cave.h"
#include "Poke_stop.h"
#include "Prof.h"
#include "Blank.h"

#include "Charizard.h"
#include "Espeon.h"
#include "Geodude.h"
#include "Mewtwo.h"
#include "Onix.h"
#include "Rayquaza.h"

#include <vector>
#include <tuple>

class Game_World {
    private:
        int length;
        int width;
        Location **grid;
        int curr_i;
        int curr_j;
        int num_blank;
        Location **blank;
        int max_abundance;

        Event* create_event(const string&, int, int);
        void move_event(Location*);
        void get_move_choices(tuple<bool, int, string>[]);
        void make_move(int);

    public:
        Game_World(int, int, int);
        ~Game_World();

        void initialize();
        void print_map() const;
        void play(bool);
        void play_game(Trainer*, bool);
};

#endif // GAME_WORLD_H
