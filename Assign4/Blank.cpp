#include "Blank.h"

Blank* Blank::clone() const {
    return new Blank;
}

int Blank::percept() const {
    return 0;
}

char Blank::get_code() const {
    return ' ';
}

int Blank::perform_event(Trainer &trainer) {
    return 0;
}
