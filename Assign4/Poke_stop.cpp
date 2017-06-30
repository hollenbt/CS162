#include "Poke_stop.h"
#include "Trainer.h"

Poke_stop* Poke_stop::clone() const {
    return new Poke_stop(*this);
}

int Poke_stop::percept() const {
    #ifndef DEBUG
        cout << '\n';
    #endif // DEBUG
    cout << "There is a Poke-stop nearby.";
    return 8;
}

char Poke_stop::get_code() const {
    return 'P';
}

int Poke_stop::perform_event(Trainer &trainer) {
    cout << "You enter the Poke-stop. ";
    int pokeballs = (rand() % 8) + 3;
    cout << "The clerk hands you " << pokeballs << " pokeballs." << endl;
    trainer.add_pokeballs(pokeballs);
    return 8;
}
