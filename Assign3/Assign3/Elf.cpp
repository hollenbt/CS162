#include "Elf.h"

// Non-default Constructor
Elf::Elf(int str, int hp, int spd, double p, double c) : Creature(str, hp, spd, p, c) {}

/*********************************************************************
** Function: Elf::get_damage
** Description: A virtual function override that calls Creature::get_damage()
**   and then evaluates whether a Magical attack triggers for double damage.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The components of the Elf's attack have all been
**   printed to the console and summed.
** Return: The damage sum.
*********************************************************************/
int Elf::get_damage() {
    int damage = Creature::get_damage();
    if (rand() % 10 == 0) {
        cout << "Magical attack doubles the damage!" << endl;
        damage *= 2;
    }
    return damage;
}

/*********************************************************************
** Function: Elf::get_winnings
** Description: A virtual function override applies the 1.5x Elf
**   payoff multiplier.
** Parameters: double p - the payoff for winning the duel.
** Pre-Conditions: N/A
** Post-Conditions: N/A
** Return: p and a half.
*********************************************************************/
double Elf::get_winnings(double p) const {
    return 1.5 * p;
}
