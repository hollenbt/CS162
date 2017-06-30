#include "Balrog.h"

// Default Constructor
Balrog::Balrog() : Demon(B_STRENGTH, B_HITPOINTS, B_SPEED, B_PAYOFF, B_COST) {}

/*********************************************************************
** Function: Balrog::get_damage
** Description: A virtual function override that calls Demon::get_damage()
**   twice because Balrogs attack twice per turn.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The components of the Balrog's attack have all been
**   printed to the console and summed.
** Return: The damage sum.
*********************************************************************/
int Balrog::get_damage() {
    int damage;
    damage = Demon::get_damage();
    damage += Demon::get_damage();
    return damage;
}

/*********************************************************************
** Function: Balrog::die
** Description: A virtual function override that prints the Balrog
**   death message.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The Balrog death message has been printed.
** Return: N/A
*********************************************************************/
void Balrog::die() const {
    cout << "The balrog shrieks and retreats to the depths from whence it came." << endl;
}

/*********************************************************************
** Function: Balrog::get_species
** Description: A virtual function override that prints "Balrog".
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: "Balrog" has been printed.
** Return: N/A
*********************************************************************/
string Balrog::get_species() const {
    return "Balrog";
}
