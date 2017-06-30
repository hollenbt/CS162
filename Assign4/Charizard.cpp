#include "Charizard.h"

// Non-default Constructor
Charizard::Charizard() : Flying("Charizard", CHARIZARD_NUMBER, CHARIZARD_EVOLVE_NUM) {}

Charizard* Charizard::clone() {
    return new Charizard(*this);
}

char Charizard::get_code() const {
    return 'C';
}
