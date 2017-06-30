#ifndef AI_H
#define AI_H

#include "Location.h"
#include "Trainer.h"
#include <tuple>

class AI : public Trainer {
    private:
        int rel_i;
        int rel_j;
        int pat_i;
        int pat_j;
        int last_move;
        int expected_result;
        int moves[2][2];
        int try_next;
        int down_count;

        bool return_to_origin;
        bool going_right;
        bool diverted;
        bool reversing;
        bool collect_pokeballs;
        bool found_poke_stop;
        bool collect_megastones;
        bool found_cave;
        bool ready_to_evolve;
        bool objectives_complete;

        int refocus();
        void set_diversion();
        void set_move(int, int);
        int check_move(int) const;
        void load_edges(tuple<bool, int, string>[]);
        void reset_results();
        int try_next_direction();
        int continue_pattern(bool check_not_move = false);
        int move_relations(int);
        int return_to_prof() const;
        int return_to_pattern();
        int find_origin();
        void get_new_target();
        void update_rel_coords(int);
        bool check_pokemon_need(int) const;
        bool check_all_stage1() const;
        int reverse_move(int) const;
        int left_perpendicular(int) const;
        int right_perpendicular(int) const;

    public:
        AI();

        void print_data() const;
        int decide_move(tuple<bool, int, string>[]);
        int decide_throw_pokeball(Pokemon*);
        void manage_inventory();
        void log_event(int);
        void add_megastone();
        void add_pokeballs(int num);
        void use_pokeball();
        void catch_pokemon(Pokemon*);
};

#endif // AI_H

/*
Percept return codes:
  0 Blank
  1 Charizard
  2 Espeon
  3 Geodude
  4 Mewtwo
  5 Onix
  6 Rayquaza
  7 Cave
  8 Poke_stop
*/
