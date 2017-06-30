#include "Mewtwo.h"

// Non-default Constructor
Mewtwo::Mewtwo() : Psychic("Mewtwo", MEWTWO_NUMBER, MEWTWO_EVOLVE_NUM) {}

Mewtwo* Mewtwo::clone() {
    return new Mewtwo(*this);
}

char Mewtwo::get_code() const {
    return 'M';
}
