#include "Creature.h"

// Non-default Constructor
Creature::Creature(int str, int hp, int spd, double p, double c) : strength(str), hitpoints(hp), speed(spd), payoff(p), cost(c) {}

// Basic Accessor Functions
int Creature::get_strength() const {
    return strength;
}

int Creature::get_hitpoints() const {
    return hitpoints;
}

int Creature::get_speed() const {
    return speed;
}

double Creature::get_payoff() const {
    return payoff;
}

double Creature::get_cost() const {
    return cost;
}

/*********************************************************************
** Function: Creature::get_damage
** Description: A virtual function that randomly generates a damage
**   number between 0 and the strength member, outputs the number to
**   the console, and returns it.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The randomly generated damage number has been output
**   to the console.
** Return: The damage number.
*********************************************************************/
int Creature::get_damage() {
    int damage;
    damage = (rand() % (strength + 1));
    cout << get_species() << " attacks for " << damage << " points!" << endl;
    return damage;
}

/*********************************************************************
** Function: Creature::take_damage
** Description: Inflicts damage upon the Creature, reducing the hitpoints
**   member and returning whether it has died or not.
** Parameters: int damage - the amount of damage taken.
** Pre-Conditions: N/A
** Post-Conditions: The hitpoints member has been reduced by damage.
** Return: True if the creature has died. False otherwise.
*********************************************************************/
bool Creature::take_damage(int damage) {
    cout << get_species() << " takes " << damage << " damage!" << endl;
    hitpoints -= damage;
    return hitpoints <= 0;
}

/*********************************************************************
** Function: Creature::die
** Description: A virtual function that announces the Creature's death
**   by printing a creature type-specific message to the console.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The Creature's death message has been printed.
** Return: N/A
*********************************************************************/
void Creature::die() const {
    cout << "The creature dies." << endl;
}

/*********************************************************************
** Function: Creature::get_winnings
** Description: A virtual function that will be overridden by derived
**   classes that apply a multiplier to the payoff.
** Parameters: double p - the payoff for winning the duel.
** Pre-Conditions: N/A
** Post-Conditions: N/A
** Return: p
*********************************************************************/
double Creature::get_winnings(double p) const {
    return p;
}

/*********************************************************************
** Function: Creature::get_species
** Description: A virtual function that prints a creature type string.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: A creature type string has been printed.
** Return: N/A
*********************************************************************/
string Creature::get_species() const {
    return "Unknown";
}
