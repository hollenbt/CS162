#include "Pokemon.h"
#include "Trainer.h"

// Non-default Constructor
Pokemon::Pokemon(const string &n, int num, int s, int nc, int nr, double cr) : name(n), number(num), stage(s), num_caught(nc), num_req(nr), catch_rate(cr) {}

// Accessors
const string& Pokemon::get_name() const {
    return name;
}


int Pokemon::get_number() const {
    return number;
}

int Pokemon::get_stage() const {
    return stage;
}

int Pokemon::get_num_caught() const {
    return num_caught;
}

int Pokemon::get_num_req() const {
    return num_req;
}

double Pokemon::get_catch_rate() const {
    return catch_rate;
}

char Pokemon::get_code() const {
    return 0;
}

// Mutators
void Pokemon::add_caught() {
    ++num_caught;
    if (!stage && num_caught == num_req)
        evolve();
}

void Pokemon::evolve() {
    ++stage;
    cout << name << " evolved to Stage " << stage << "!\n" << endl;
}

void Pokemon::print() const {
    cout << name << endl << "Stage: " << stage << endl;
    cout << "Caught: " << num_caught << " / " << num_req << '\n' << endl;
}

Pokemon* Pokemon::clone() const {
    return new Pokemon(*this);
}

int Pokemon::percept() const {
    #ifndef DEBUG
        cout << '\n';
    #endif // DEBUG
    cout << "You hear a wild " << name << " nearby.";
    return number;
}

/*********************************************************************
** Function: Pokemon::perform_event
** Description: Conducts the encounter with a wild Pokemon. Asks the
**   player (or AI) whether they would like to use a pokeball to attempt
**   to catch the Pokemon, and calls the necessary member functions if
**   the pokeball is thrown and if the Pokemon is caught.
** Parameters: Trainer &trainer - a reference to a Trainer or AI object
** Pre-Conditions: N/A
** Post-Conditions: If the trainer threw a pokeball, and if the Pokemon
**   was caught, the necessary member functions have been called.
** Return: the Pokemon's id number
*********************************************************************/
int Pokemon::perform_event(Trainer &trainer) {
    cout << "A wild " << name << " appeared!" << endl;
    if (!trainer.get_pokeballs())
        cout << "You don't have any pokeballs! Visit a Poke-stop to get some." << endl;
    else {
        int throw_ball = trainer.decide_throw_pokeball(this);
        if (throw_ball == 1) {
            trainer.use_pokeball();
            if (static_cast<double>(rand() % 100)/100 < catch_rate) {
                cout << "You caught the " << name << '!' << endl;
                trainer.catch_pokemon(this);
                return number;
            }
            else cout << "So close! It appeared to be caught!" << endl;
        }
    }
    cout << "The wild " << name << " flees." << endl;
    return number;
}
