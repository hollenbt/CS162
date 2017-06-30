#include "Rayquaza.h"

// Non-default Constructor
Rayquaza::Rayquaza() : Flying("Rayquaza", RAYQUAZA_NUMBER, RAYQUAZA_EVOLVE_NUM) {}

Rayquaza* Rayquaza::clone() {
    return new Rayquaza(*this);
}

char Rayquaza::get_code() const {
    return 'R';
}
