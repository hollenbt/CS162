#ifndef POKEMON_H
#define POKEMON_H

#include "Event.h"
#define NUM_POKEMON 6

#ifdef DEBUG
    #define MAX_EVOLVE_NUM 1
#else
    #define MAX_EVOLVE_NUM 3
#endif


class Pokemon : public Event {
    protected:
        string name;
        int number;
        int stage;
        int num_caught;
        int num_req;
        double catch_rate;
        Pokemon(const string&, int, int, int, int, double);
    public:
        const string& get_name() const;
        int get_number() const;
        int get_stage() const;
        int get_num_caught() const;
        int get_num_req() const;
        double get_catch_rate() const;

        void add_caught();
        void evolve();

        void print() const;
        Pokemon* clone() const;
        int percept() const;
        char get_code() const;
        int perform_event(Trainer&);

};

#endif // POKEMON_H
