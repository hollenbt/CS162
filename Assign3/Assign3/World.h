#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Human.h"
#include "High_elf.h"
#include "Dryad.h"
#include "Balrog.h"
#include "Cyberdemon.h"

#include <algorithm>

class World {
    private:
        int num_humans;
        Human *humans;
        int num_high_elves;
        High_elf *high_elves;
        int num_dryads;
        Dryad *dryads;
        int num_balrogs;
        Balrog *balrogs;
        int num_cdemons;
        Cyberdemon *cdemons;
        double bank;
        double g_earned;
        double g_spent;

        int find_in_array(Creature*, int, Creature*);

    public:
        // Default and Non-default Constructor and the Big Three
        World();
        World(int, int, int, int, int, double, double, double);
        ~World();
        World(const World&);
        void operator=(World);
        friend void swap(World&, World&);

        // Accessor Functions
        Human* get_humans();
        int get_num_humans() const;
        High_elf* get_high_elves();
        int get_num_high_elves() const;
        Dryad* get_dryads();
        int get_num_dryads() const;
        Balrog* get_balrogs();
        int get_num_balrogs() const;
        Cyberdemon* get_cdemons();
        int get_num_cdemons() const;
        double get_bank() const;
        double get_gold_earned() const;
        double get_gold_spent() const;
        Creature* get_creature(int);
        int get_num_creatures() const;

        // Mutator Functions
        void add_humans(int);
        void add_high_elves(int);
        void add_dryads(int);
        void add_balrogs(int);
        void add_cdemons(int);
        void remove_dead(Creature*);
        void remove_human(int);
        void remove_high_elf(int);
        void remove_dryad(int);
        void remove_balrog(int);
        void remove_cdemon(int);
        void add_money(double);
        void spend_money(double);

        void display_creatures() const;
        void battle(Creature*, Creature*);

        template<typename T>
        friend void copy(T*, T*, int);
};

#endif // WORLD_H_INCLUDED
