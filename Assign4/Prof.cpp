#include "Prof.h"
#include "Pokemon.h"
#include "Trainer.h"

Prof* Prof::clone() const {
    return new Prof;
}

int Prof::percept() const {
    #ifdef DEBUG
        cout << "Professor Oak is here.";
    #endif // DEBUG
    return 0;
}

char Prof::get_code() const {
    return 'X';
}

/*********************************************************************
** Function: Prof::perform_event
** Description: Conducts the player's interactions with Professor Oak.
**   Ends the game if all Pokemon have been caught and raised to Stage 2.
** Parameters: Trainer &trainer - reference to a Trainer or AI object.
** Pre-Conditions: N/A
** Post-Conditions: N/A
** Return: -1 if the game should end, 0 otherwise.
*********************************************************************/
int Prof::perform_event(Trainer &trainer) {
    int i = 0;
    bool stage2 = true;
    Pokemon **pkmn = trainer.get_pokemon();
    while (i < NUM_POKEMON && pkmn[i]) {
        if (!(stage2 = (pkmn[i++]->get_stage() == 2)))
            break;
    }
    if (i == NUM_POKEMON && stage2) {
        cout << "Congratulations! You are now a Pokemon Champion! I knew you could do it.\n"
             << "Now hand them over so I can perform some ethically questionable experiments!\n" << endl;
        return -1;
    }
    cout << "You still haven't caught and raised all the Pokemon to Stage 2!\n";
    cout << "Come find me when you get your act together." << endl;
    return 0;
}
