#include "Trainer.h"

// Default Constructor
Trainer::Trainer() : megastones(0), pokeballs(0), pokemon() {}

// Destructor
Trainer::~Trainer() {
    for (int i = 0; i < NUM_POKEMON; ++i)
        delete pokemon[i];
}

// Accessors
int Trainer::get_megastones() const {
    return megastones;
}

int Trainer::get_pokeballs() const {
    return pokeballs;
}

Pokemon** Trainer::get_pokemon() {
    return pokemon;
}

// Mutators
void Trainer::add_megastone() {
    ++megastones;
}

void Trainer::add_pokeballs(int num) {
    pokeballs += num;
}

void Trainer::use_pokeball() {
    --pokeballs;
}

/*********************************************************************
** Function: Trainer::find_pokemon
** Description: Searches the pokemon array for a Pokemon with the supplied
**   id number. If found, true is returned and the index is passed out by
**   reference. If not, false is returned and the first empty array
**   index is passed out by reference.
** Parameters: int &index_out - the passed out index
**             int pkmn_number - the Pokemon's id number
** Pre-Conditions: pkmn_number is a valid Pokemon id number [1-6]
** Post-Conditions: If found, index_out contains the Pokemon's index. If
**   not, index_out contains the first empty array index.
** Return: true if found, false if not.
*********************************************************************/
bool Trainer::find_pokemon(int &index_out, int pkmn_number) const {
    index_out = -1;
    while (pokemon[++index_out]) {
        if (pokemon[index_out]->get_number() == pkmn_number)
            return true;
    }
    return false;
}

/*********************************************************************
** Function: Trainer::catch_pokemon
** Description: Updates the pokemon array to reflect the pkmn being
**   caught.
** Parameters: Pokemon *pkmn - the caught Pokemon
** Pre-Conditions: pkmn is not a null pointer.
** Post-Conditions: The pokemon array has been updated to reflect
**   pkmn being caught.
** Return: N/A
*********************************************************************/
void Trainer::catch_pokemon(Pokemon *pkmn) {
    int i;
    if (!find_pokemon(i, pkmn->get_number()))
        pokemon[i] = pkmn->clone();
    pokemon[i]->add_caught();
}

/*********************************************************************
** Function: Trainer::print_inventory
** Description: Prints the caught Pokemon stats, and the number of
**   megastones and pokeballs collected.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: All Pokemon have been printed, as well as the number
**   of megastones and pokeballs currently held.
** Return: the number of distinct Pokemon caught
*********************************************************************/
int Trainer::print_inventory() {
    int i = 0;
    while (i < NUM_POKEMON && pokemon[i]) {
        cout << i+1 << ". ";
        pokemon[i++]->print();
    }
    cout << "Megastones: " << megastones << endl;
    cout << "Pokeballs: " << pokeballs << '\n' << endl;
    return i;
}

/*********************************************************************
** Function: Trainer::manage_inventory
** Description: Shows the player their inventory, allowing them to
**   check Pokemon and item stats and evolve any Stage 1 Pokemon to
**   Stage 2 if megastones have been acquired.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Pokemon stage has been incremented and megastones
**   has been decremented, if applicable.
** Return: N/A
*********************************************************************/
void Trainer::manage_inventory() {
    int i = print_inventory();
    int choice;
    string prompt1 = "1. Evolve a Pokemon to Stage 2.\n2. Exit.\n\n";
    get_pos_integer(prompt1, &choice, 2);
    while (choice == 1) {
        if (!megastones) {
            cout << "You don't have any megastones!\n" << endl;
            return;
        }
        string prompt2 = "Choose a Pokemon to evolve: ";
        get_pos_integer(prompt2, &choice, i);
        if (pokemon[choice - 1]->get_stage() == 1) {
            pokemon[choice - 1]->evolve();
            --megastones;
        }
        else cout << pokemon[choice - 1]->get_name() << " isn't Stage 1.\n" << endl;
        print_inventory();
        get_pos_integer(prompt1, &choice, 2);
    }
}

/*********************************************************************
** Function: Trainer::get_move_prompt
** Description: Uses a stringstream object to create a move prompt string.
** Parameters: tuple<bool, int, string> move_choices[] - a four element
**               tuple array
** Pre-Conditions: move_choices has been loaded with information from
**   the adjacent grid Locations.
** Post-Conditions: N/A
** Return: The movement option string, containing only valid moves.
*********************************************************************/
string Trainer::get_move_prompt(tuple<bool, int, string> move_choices[]) {
    stringstream prompt;
    prompt << "\n\n";
    for (int i = 0; i < 4; ++i)
        if (get<0>(move_choices[i]))
            prompt << i + 1 << ". Go " << get<2>(move_choices[i]) << ".\n";
    prompt << "5. View Pokemon/Inventory.\n\n";
    return prompt.str();
}

/*********************************************************************
** Function: Trainer::decide_move
** Description: Gets a move number from the player.
** Parameters: tuple<bool, int, string> move_choices[] - a four element
**               tuple array
** Pre-Conditions: move_choices has been loaded with information from
**   the adjacent grid Locations.
** Post-Conditions: N/A
** Return: The user-supplied movement number.
*********************************************************************/
int Trainer::decide_move(tuple<bool, int, string> move_choices[]) {
    string prompt = get_move_prompt(move_choices);
    int choice;
    do {
        get_pos_integer(prompt, &choice, 5);
    } while (choice != 5 && !get<0>(move_choices[choice - 1]));
    return choice;
}

/*********************************************************************
** Function: Trainer::decide_throw_pokeball
** Description: Asks whether to use a pokeball to attempt to catch the
**   the Pokemon.
** Parameters: Pokemon *pkmn - the encountered Pokemon
** Pre-Conditions: pkmn is not null.
** Post-Conditions: N/A
** Return: The player's decision.
*********************************************************************/
int Trainer::decide_throw_pokeball(Pokemon *pkmn) {
    int throw_ball;
    string prompt = "Throw a pokeball at " + pkmn->get_name() + "? (1 - yes, 2 - no) ";
    get_pos_integer(prompt, &throw_ball, 2);
    return throw_ball;
}

void Trainer::log_event(int event_result) {}
