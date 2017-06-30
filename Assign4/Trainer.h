#ifndef TRAINER_H
#define TRAINER_H


#include "Pokemon.h"
#include <sstream>
#include <tuple>

class Trainer {
    protected:
        int megastones;
        int pokeballs;
        Pokemon *pokemon[NUM_POKEMON];

        bool find_pokemon(int&, int) const;

        string get_move_prompt(tuple<bool, int, string>[]);

    public:
        Trainer();
        virtual ~Trainer();

        int get_megastones() const;
        int get_pokeballs() const;
        Pokemon** get_pokemon();

        virtual void add_megastone();
        virtual void add_pokeballs(int num);
        virtual void use_pokeball();
        virtual void catch_pokemon(Pokemon*);

        virtual int decide_move(tuple<bool, int, string>[]);
        virtual int decide_throw_pokeball(Pokemon*);
        virtual void manage_inventory();
        virtual void log_event(int);

        int print_inventory();
};

#endif // TRAINER_H
