#include "Cyberdemon.h"

// Default Constructor
Cyberdemon::Cyberdemon() : Demon(C_STRENGTH, C_HITPOINTS, C_SPEED, C_PAYOFF, C_COST) {}

/*********************************************************************
** Function: Cyberdemon::die
** Description: A virtual function override that prints the Cyberdemon
**   death message.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The Cyberdemon death message has been printed.
** Return: N/A
*********************************************************************/
void Cyberdemon::die() const {
    cout << "The cyberdemon disappears, banished to the matrix." << endl;
}

/*********************************************************************
** Function: Cyberdemon::get_species
** Description: A virtual function override that prints "Cyberdemon".
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: "Cyberdemon" has been printed.
** Return: N/A
*********************************************************************/
string Cyberdemon::get_species() const {
    return "Cyberdemon";
}
