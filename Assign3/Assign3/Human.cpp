#include "Human.h"

// Default Constructor
Human::Human() : Creature(H_STRENGTH, H_HITPOINTS, H_SPEED, H_PAYOFF, H_COST) {}

/*********************************************************************
** Function: Human::die
** Description: A virtual function override that prints the Human
**   death message.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The Human death message has been printed.
** Return: N/A
*********************************************************************/
void Human::die() const {
    cout << "The human calls out for his family as the last glimmer of life in him is extinguished." << endl;
}

/*********************************************************************
** Function: Human::get_winnings
** Description: A virtual function override applies the 2x Human
**   payoff multiplier.
** Parameters: double p - the payoff for winning the duel.
** Pre-Conditions: N/A
** Post-Conditions: N/A
** Return: Twice p.
*********************************************************************/
double Human::get_winnings(double p) const {
    return 2 * p;
}

/*********************************************************************
** Function: Human::get_species
** Description: A virtual function override that prints "Human".
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: "Human" has been printed.
** Return: N/A
*********************************************************************/
string Human::get_species() const {
    return "Human";
}
