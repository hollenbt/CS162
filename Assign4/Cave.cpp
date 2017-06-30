#include "Cave.h"
#include "Trainer.h"

Cave* Cave::clone() const {
    return new Cave(*this);
}

int Cave::percept() const {
    #ifndef DEBUG
        cout << '\n';
    #endif // DEBUG
    cout << "You see a cave nearby.";
    return 7;
}
char Cave::get_code() const {
    return 'V';
}

int Cave::perform_event(Trainer &trainer) {
    cout << "You enter a cave.\nYou find a megastone! You can use it to evolve your Stage 1 Pokemon to Stage 2." << endl;
    trainer.add_megastone();
    return 7;
}
