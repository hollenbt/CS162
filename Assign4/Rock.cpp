#include "Rock.h"

// Non-default Constructor
Rock::Rock(const string &name, int number, int num_req) : Pokemon(name, number, 0, 0, num_req, 0.75) {}
