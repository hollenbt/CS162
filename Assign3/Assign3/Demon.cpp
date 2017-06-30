#include "Demon.h"

// Non-default Constructor
Demon::Demon(int str, int hp, int spd, double p, double c) : Creature(str, hp, spd, p, c) {}

/*********************************************************************
** Function: Demon::get_damage
** Description: A virtual function override that calls Creature::get_damage()
**   and then evaluates whether a Demonic attack triggers for an
**   additional 50 damage.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The components of the Demon's attack have all been
**   printed to the console and summed.
** Return: The damage sum.
*********************************************************************/
int Demon::get_damage() {
    int damage;
    damage = Creature::get_damage();
    if (rand() % 20 == 0) {
        cout << "Demonic attack inflicts 50 additional damage!" << endl;
        damage += 50;
    }
    return damage;
}
