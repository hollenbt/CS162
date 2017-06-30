#include "Dryad.h"

// Default Constructor
Dryad::Dryad() : Elf(D_STRENGTH, D_HITPOINTS, D_SPEED, D_PAYOFF, D_COST) {}

/*********************************************************************
** Function: Dryad::set_health
** Description: Sets the Dryad's hitpoints to the passed value. (For use
**   implementing the Dryad's special ability.)
** Parameters: int h - the value to which hitpoints will be set.
** Pre-Conditions: N/A
** Post-Conditions: hitpoints has been set to h.
** Return: N/A
*********************************************************************/
void Dryad::set_health(int h) {
    hitpoints = h;
}

/*********************************************************************
** Function: Dryad::get_damage
** Description: A virtual function override that calls Elf::get_damage()
**   and then evaluates whether the Dryad special ability triggers. If so,
**   resets hitpoints to D_HITPOINTS.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The components of the Dryad's attack have all been
**   printed to the console and summed. The Dryad's hitpoints have been
**   set to D_HITPOINTS if the special ability triggered.
** Return: The damage sum.
*********************************************************************/
int Dryad::get_damage() {
    int damage;
    damage = Elf::get_damage();
    if (rand() % 20 == 0) {
        cout << "Dryad communes with nature and heals to full health." << endl;
        set_health(D_HITPOINTS);
    }
    return damage;
}

/*********************************************************************
** Function: Dryad::die
** Description: A virtual function override that prints the Dryad
**   death message.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The Dryad death message has been printed.
** Return: N/A
*********************************************************************/
void Dryad::die() const {
    cout << "The dryad sighs, and her spirit returns to the forest of her ancestors." << endl;
}

/*********************************************************************
** Function: Dryad::get_species
** Description: A virtual function override that prints "Dryad".
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: "Dryad" has been printed.
** Return: N/A
*********************************************************************/
string Dryad::get_species() const {
    return "Dryad";
}
