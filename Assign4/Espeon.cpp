#include "Espeon.h"

// Non-default Constructor
Espeon::Espeon() : Psychic("Espeon", ESPEON_NUMBER, ESPEON_EVOLVE_NUM) {}

Espeon* Espeon::clone() {
    return new Espeon(*this);
}

char Espeon::get_code() const {
    return 'E';
}
