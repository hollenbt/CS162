#include "High_elf.h"

// Default Constructor
High_elf::High_elf() : Elf(E_STRENGTH, E_HITPOINTS, E_SPEED, E_PAYOFF, E_COST) {}

/*********************************************************************
** Function: High_elf::die
** Description: A virtual function override that prints the High_elf
**   death message.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The High_elf death message has been printed.
** Return: N/A
*********************************************************************/
void High_elf::die() const {
    cout << "The high elf calmly accepts his fate and vanishes in a poof of dust." << endl;
}

/*********************************************************************
** Function: High_elf::get_species
** Description: A virtual function override that prints "High elf".
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: "High elf" has been printed.
** Return: N/A
*********************************************************************/
string High_elf::get_species() const {
    return "High elf";
}
