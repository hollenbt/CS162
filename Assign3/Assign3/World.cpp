#include "World.h"

// Default Constructor
World::World() : num_humans(0), humans(0), num_high_elves(0), high_elves(0),
                 num_dryads(0), dryads(0), num_balrogs(0), balrogs(0),
                 num_cdemons(0), cdemons(0), bank(0), g_earned(0), g_spent(0)
{
}

// Non-default Constructor
World::World(int h, int e, int d, int b, int c, double m, double g_e = 0, double g_s = 0) :
    num_humans(h), humans(new Human[h]),
    num_high_elves(e), high_elves(new High_elf[e]),
    num_dryads(d), dryads(new Dryad[d]),
    num_balrogs(b), balrogs(new Balrog[b]),
    num_cdemons(c), cdemons(new Cyberdemon[c]),
    bank(m), g_earned(g_e), g_spent(g_s)
{
}

// Destructor
World::~World() {
    delete[] humans;
    delete[] high_elves;
    delete[] dryads;
    delete[] balrogs;
    delete[] cdemons;
}

// Copy Constructor
World::World(const World &w) :
    num_humans(w.num_humans), humans(new Human[num_humans]),
    num_high_elves(w.num_high_elves), high_elves(new High_elf[num_high_elves]),
    num_dryads(w.num_dryads), dryads(new Dryad[num_dryads]),
    num_balrogs(w.num_balrogs), balrogs(new Balrog[num_balrogs]),
    num_cdemons(w.num_cdemons), cdemons(new Cyberdemon[num_cdemons]),
    bank(w.bank), g_earned(w.g_earned), g_spent(w.g_spent)
{
    for (int i = 0; i < num_humans; ++i)
        humans[i] = w.humans[i];
    for (int i = 0; i < num_high_elves; ++i)
        high_elves[i] = w.high_elves[i];
    for (int i = 0; i < num_dryads; ++i)
        dryads[i] = w.dryads[i];
    for (int i = 0; i < num_balrogs; ++i)
        balrogs[i] = w.balrogs[i];
    for (int i = 0; i < num_cdemons; ++i)
        cdemons[i] = w.cdemons[i];
}

// Assignment Operator Overload
void World::operator=(World that) {
    swap(*this, that);
}

void swap(World &w1, World &w2) {
    std::swap(w1.humans, w2.humans);
    std::swap(w1.num_humans, w2.num_humans);
    std::swap(w1.high_elves, w2.high_elves);
    std::swap(w1.num_high_elves, w2.num_high_elves);
    std::swap(w1.dryads, w2.dryads);
    std::swap(w1.num_dryads, w2.num_dryads);
    std::swap(w1.balrogs, w2.balrogs);
    std::swap(w1.num_balrogs, w2.num_balrogs);
    std::swap(w1.cdemons, w2.cdemons);
    std::swap(w1.num_cdemons, w2.num_cdemons);
    std::swap(w1.bank, w2.bank);
    std::swap(w1.g_earned, w2.g_earned);
    std::swap(w1.g_spent, w2.g_spent);
}

// Basic Accessor Functions
Human* World::get_humans() {
    return humans;
}

int World::get_num_humans() const {
    return num_humans;
}

High_elf* World::get_high_elves() {
    return high_elves;
}

int World::get_num_high_elves() const {
    return num_high_elves;
}

Dryad* World::get_dryads() {
    return dryads;
}

int World::get_num_dryads() const {
    return num_dryads;
}

Balrog* World::get_balrogs() {
    return balrogs;
}

int World::get_num_balrogs() const {
    return num_balrogs;
}

Cyberdemon* World::get_cdemons() {
    return cdemons;
}

int World::get_num_cdemons() const {
    return num_cdemons;
}

double World::get_bank() const {
    return bank;
}

double World::get_gold_earned() const {
    return g_earned;
}

double World::get_gold_spent() const {
    return g_spent;
}

/*********************************************************************
** Function: World::get_creature
** Description: Takes a cumulative index of all creature type arrays
**   (ordered humans, high_elves, dryads, balrogs, cdemons) and returns
**   a pointer to the corresponding Creature.
** Parameters: int index - the index of the selected creature.
** Pre-Conditions: index is less than the sum of all array size (num_humans,
**   num_high_elves, etc.) member variables.
** Post-Conditions: N/A
** Return: A pointer to the selected Creature object.
*********************************************************************/
Creature* World::get_creature(int index) {
    if (index < num_humans)
        return &humans[index];
    index -= num_humans;

    if (index < num_high_elves)
        return &high_elves[index];
    index -= num_high_elves;

    if (index < num_dryads)
        return &dryads[index];
    index -= num_dryads;

    if (index < num_balrogs)
        return &balrogs[index];
    index -= num_balrogs;

    return &cdemons[index];
}

/*********************************************************************
** Function: World::get_num_creatures
** Description: Returns the sum of all array size member variables
**   (i.e. num_humans, num_high_elves, etc.).
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: N/A
** Return: The total number of creatures in the World object.
*********************************************************************/
int World::get_num_creatures() const {
    return num_humans + num_high_elves + num_dryads + num_balrogs + num_cdemons;
}

/*********************************************************************
** Function: World::add_humans
** Description: Checks that the user can afford to recruit n humans,
**   and adds them to the humans array and updates num_humans if so.
** Parameters: int n - the number of Human objects to add.
** Pre-Conditions: N/A
** Post-Conditions: If the user has enough gold, the humans array has
**   been resized to hold n additional Human objects and num_humans has
**   been increased by n. Otherwise, the user has been informed that
**   they did not have enough money and no changes have been made.
** Return: N/A
*********************************************************************/
void World::add_humans(int n) {
    if (bank < H_COST * n) {
        cout << "Not enough money." << endl;
        return;
    }
    spend_money(H_COST * n);
    Human *temp = humans;
    humans = new Human[num_humans + n];
    copy(temp, humans, num_humans);
    num_humans += n;
    delete[] temp;
}

/*********************************************************************
** Function: World::add_high_elves
** Description: Checks that the user can afford to recruit n high elves,
**   and adds them to the high_elves array and updates num_high_elves if so.
** Parameters: int n - the number of High_elf objects to add.
** Pre-Conditions: N/A
** Post-Conditions: If the user has enough gold, the high_elves array has
**   been resized to hold n additional High_elf objects and num_high_elves has
**   been increased by n. Otherwise, the user has been informed that
**   they did not have enough money and no changes have been made.
** Return: N/A
*********************************************************************/
void World::add_high_elves(int n) {
    if (bank < E_COST * n) {
        cout << "Not enough money." << endl;
        return;
    }
    spend_money(E_COST * n);
    High_elf *temp = high_elves;
    high_elves = new High_elf[num_high_elves + n];
    copy(temp, high_elves, num_high_elves);
    num_high_elves += n;
    delete[] temp;
}

/*********************************************************************
** Function: World::add_dryads
** Description: Checks that the user can afford to recruit n dryads,
**   and adds them to the dryads array and updates num_dryads if so.
** Parameters: int n - the number of Dryad objects to add.
** Pre-Conditions: N/A
** Post-Conditions: If the user has enough gold, the dryads array has
**   been resized to hold n additional Dryad objects and num_dryads has
**   been increased by n. Otherwise, the user has been informed that
**   they did not have enough money and no changes have been made.
** Return: N/A
*********************************************************************/
void World::add_dryads(int n) {
    if (bank < D_COST * n) {
        cout << "Not enough money." << endl;
        return;
    }
    spend_money(D_COST * n);
    Dryad *temp = dryads;
    dryads = new Dryad[num_dryads + n];
    copy(temp, dryads, num_dryads);
    num_dryads += n;
    delete[] temp;
}

/*********************************************************************
** Function: World::add_balrogs
** Description: Checks that the user can afford to recruit n balrogs,
**   and adds them to the balrogs array and updates num_balrogs if so.
** Parameters: int n - the number of Balrog objects to add.
** Pre-Conditions: N/A
** Post-Conditions: If the user has enough gold, the balrogs array has
**   been resized to hold n additional Balrog objects and num_balrogs has
**   been increased by n. Otherwise, the user has been informed that
**   they did not have enough money and no changes have been made.
** Return: N/A
*********************************************************************/
void World::add_balrogs(int n) {
    if (bank < B_COST * n) {
        cout << "Not enough money." << endl;
        return;
    }
    spend_money(B_COST * n);
    Balrog *temp = balrogs;
    balrogs = new Balrog[num_balrogs + n];
    copy(temp, balrogs, num_balrogs);
    num_balrogs += n;
    delete[] temp;
}

/*********************************************************************
** Function: World::add_cdemons
** Description: Checks that the user can afford to recruit n cdemons,
**   and adds them to the cdemons array and updates num_cdemons if so.
** Parameters: int n - the number of Cyberdemon objects to add.
** Pre-Conditions: N/A
** Post-Conditions: If the user has enough gold, the cdemons array has
**   been resized to hold n additional Cyberdemon objects and num_cdemons has
**   been increased by n. Otherwise, the user has been informed that
**   they did not have enough money and no changes have been made.
** Return: N/A
*********************************************************************/
void World::add_cdemons(int n) {
    if (bank < C_COST * n) {
        cout << "Not enough money." << endl;
        return;
    }
    spend_money(C_COST * n);
    Cyberdemon *temp = cdemons;
    cdemons = new Cyberdemon[num_cdemons + n];
    copy(temp, cdemons, num_cdemons);
    num_cdemons += n;
    delete[] temp;
}

/*********************************************************************
** Function: World::find_in_array
** Description: Checks that the user can afford to recruit n humans,
**   and adds them to the humans array and updates num_humans if so.
** Parameters: Creature *arr - the Creature array to search.
**             int size - the size of the Creature array.
**             Creature *elem - a pointer to the Creature object to
**               search for.
** Pre-Conditions: arr contains at least size elements.
** Post-Conditions: N/A
** Return: The index of the Creature element, if found. Otherwise -1.
*********************************************************************/
int World::find_in_array(Creature *arr, int size, Creature *elem) {
    for (int i = 0; i < size; ++i) {
        if (arr + i == elem)
            return i;
    }
    return -1;
}

/*********************************************************************
** Function: World::remove_dead
** Description: Removes a dead Creature from the World.
** Parameters: Creature *dead - a pointer to the Creature to be removed.
** Pre-Conditions: N/A
** Post-Conditions: If dead was found in any of the member arrays, it
**   have been removed from the World. Otherwise, the user has been
**   notified that the Creature was not found.
** Return: N/A
*********************************************************************/
void World::remove_dead(Creature *dead) {
    int index;
    if ((index = find_in_array(humans, num_humans, dead)) != -1) {
        remove_human(index);
        return;
    }
    if ((index = find_in_array(high_elves, num_high_elves, dead)) != -1) {
        remove_high_elf(index);
        return;
    }
    if ((index = find_in_array(dryads, num_dryads, dead)) != -1) {
        remove_dryad(index);
        return;
    }
    if ((index = find_in_array(balrogs, num_balrogs, dead)) != -1) {
        remove_balrog(index);
        return;
    }
    if ((index = find_in_array(cdemons, num_cdemons, dead)) != -1) {
        remove_cdemon(index);
        return;
    }
    cout << "Creature not found." << endl;
}

/*********************************************************************
** Function: World::remove_human
** Description: Removes the Human object at index from the humans array.
**   Resizes the humans array and decrements num_humans.
** Parameters: int index - the index of the Human to be removed.
** Pre-Conditions: index < num_humans
** Post-Conditions: The Human at index has been removed, the humans
**   array has been resized, and num_humans has been decremented.
** Return: N/A
*********************************************************************/
void World::remove_human(int index) {
    Human *temp = humans;
    humans = new Human[num_humans - 1];
    copy(temp, humans, index);
    copy(temp + index + 1, humans + index, num_humans - (index + 1));
    --num_humans;
    delete[] temp;
}

/*********************************************************************
** Function: World::remove_high_elf
** Description: Removes the High_elf object at index from the high_elves array.
**   Resizes the high_elves array and decrements num_high_elves.
** Parameters: int index - the index of the High_elf to be removed.
** Pre-Conditions: index < num_high_elves
** Post-Conditions: The High_elf at index has been removed, the high_elves
**   array has been resized, and num_high_elves has been decremented.
** Return: N/A
*********************************************************************/
void World::remove_high_elf(int index) {
    High_elf *temp = high_elves;
    high_elves = new High_elf[num_high_elves - 1];
    copy(temp, high_elves, index);
    copy(temp + index + 1, high_elves + index, num_high_elves - (index + 1));
    --num_high_elves;
    delete[] temp;
}

/*********************************************************************
** Function: World::remove_dryad
** Description: Removes the Dryad object at index from the dryads array.
**   Resizes the dryads array and decrements num_dryads.
** Parameters: int index - the index of the Dryad to be removed.
** Pre-Conditions: index < num_dryads
** Post-Conditions: The Dryad at index has been removed, the dryads
**   array has been resized, and num_dryads has been decremented.
** Return: N/A
*********************************************************************/
void World::remove_dryad(int index) {
    Dryad *temp = dryads;
    dryads = new Dryad[num_dryads - 1];
    copy(temp, dryads, index);
    copy(temp + index + 1, dryads + index, num_dryads - (index + 1));
    --num_dryads;
    delete[] temp;
}

/*********************************************************************
** Function: World::remove_balrog
** Description: Removes the Balrog object at index from the balrogs array.
**   Resizes the balrogs array and decrements num_balrogs.
** Parameters: int index - the index of the Balrog to be removed.
** Pre-Conditions: index < num_balrogs
** Post-Conditions: The Balrog at index has been removed, the balrogs
**   array has been resized, and num_balrogs has been decremented.
** Return: N/A
*********************************************************************/
void World::remove_balrog(int index) {
    Balrog *temp = balrogs;
    balrogs = new Balrog[num_balrogs - 1];
    copy(temp, balrogs, index);
    copy(temp + index + 1, balrogs + index, num_balrogs - (index + 1));
    --num_balrogs;
    delete[] temp;
}

/*********************************************************************
** Function: World::remove_cdemon
** Description: Removes the Cyberdemon object at index from the cdemons array.
**   Resizes the cdemons array and decrements num_cdemons.
** Parameters: int index - the index of the Cyberdemon to be removed.
** Pre-Conditions: index < num_cdemons
** Post-Conditions: The Cyberdemon at index has been removed, the cdemons
**   array has been resized, and num_cdemons has been decremented.
** Return: N/A
*********************************************************************/
void World::remove_cdemon(int index) {
    Cyberdemon *temp = cdemons;
    cdemons = new Cyberdemon[num_cdemons - 1];
    copy(temp, cdemons, index);
    copy(temp + index + 1, cdemons + index, num_cdemons - (index + 1));
    --num_cdemons;
    delete[] temp;
}

/*********************************************************************
** Function: copy
** Description: Copies elements from one array to another.
** Parameters: T *src - the source array.
**             T *dest - the destination array.
**             int num - the number of elements to copy.
** Pre-Conditions: Both src and dest contain at least num elements.
** Post-Conditions: The first num elements of src have been copied to
**   the first num elements of dest.
** Return: N/A
*********************************************************************/
template<typename T>
void copy(T *src, T *dest, int num) {
    for (int i = 0; i < num; ++i)
        dest[i] = src[i];
}

/*********************************************************************
** Function: World::add_money
** Description: Adds gold to the bank member and the g_earned member.
** Parameters: double money - the amount of gold to add.
** Pre-Conditions: Both src and dest contain at least num elements.
** Post-Conditions: The values of the bank and g_earned members have
**   been increased by money, and a confirmation message has been printed.
** Return: N/A
*********************************************************************/
void World::add_money(double money) {
    cout << money << " coins added to the bank." << endl;
    bank += money;
    g_earned += money;
}

/*********************************************************************
** Function: World::spend_money
** Description: Removes gold from the bank member and add the same amount
**   to the g_spent member.
** Parameters: double money - the amount of gold to remove.
** Pre-Conditions: N/A
** Post-Conditions: The values of the bank and g_earned members have
**   been increased and decreased by money, respectively.
** Return: N/A
*********************************************************************/
void World::spend_money(double money) {
    bank -= money;
    g_spent += money;
}

/*********************************************************************
** Function: World::display_creatures
** Description: Prints the creature type and hitpoints of all Creatures
**   in the five dynamic arrays of the World class, numbered, in the
**   same order that they will be accessed in World::get_creature().
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The Creatures and their hitpoints have been printed
**   to the console, numbered and in order.
** Return: N/A
*********************************************************************/
void World::display_creatures() const {
    int c = 0;
    cout << "\nGladiators:\n";
    if (!get_num_creatures()) {
        cout << "\tNone\n";
        return;
    }
    for (int i = 0; i < num_humans; ++i)
        cout << ++c << ". Human (Hitpoints: " << humans[i].get_hitpoints() << ")\n";
    for (int i = 0; i < num_high_elves; ++i)
        cout << ++c << ". High elf (Hitpoints: " << high_elves[i].get_hitpoints() << ")\n";
    for (int i = 0; i < num_dryads; ++i)
        cout << ++c << ". Dryad (Hitpoints: " << dryads[i].get_hitpoints() << ")\n";
    for (int i = 0; i < num_balrogs; ++i)
        cout << ++c << ". Balrog (Hitpoints: " << balrogs[i].get_hitpoints() << ")\n";
    for (int i = 0; i < num_cdemons; ++i)
        cout << ++c << ". Cyberdemon (Hitpoints: " << cdemons[i].get_hitpoints() << ")\n";

}

/*********************************************************************
** Function: World::battle
** Description: Conducts a turn by turn battle between two Creatures
**   until one dies, with text narration. Removes the dead Creature
**   from the World and adds the gold earned to the bank.
** Parameters: Creature *c1 - the first combatant.
**             Creature *c2 - the second combatant.
** Pre-Conditions: c1 and c2 are not null pointers.
** Post-Conditions: The battle has been narrated, one Creature has died
**   and been removed from the World, and the payoff (including the
**   victorious-creature-dependent multiplier) has been added to the
**   bank.
** Return: N/A
*********************************************************************/
void World::battle(Creature *c1, Creature *c2) {
    bool kill = false;
    if (c1->get_speed() > c2->get_speed()) {
        cout << endl;
        kill = c2->take_damage(c1->get_damage());
        cout << c1->get_species() << " hitpoints: " << c1->get_hitpoints() << endl << c2->get_species() << " hitpoints: " << c2->get_hitpoints() << endl;
    }
    while (!kill) {
        cout << endl;
        kill = c1->take_damage(c2->get_damage());
        cout << c1->get_species() << " hitpoints: " << c1->get_hitpoints() << endl << c2->get_species() << " hitpoints: " << c2->get_hitpoints() << endl;
        if (kill) {
            c1->die();
            add_money(c2->get_winnings(c1->get_payoff()));
            remove_dead(c1);
            return;
        }
        cout << endl;
        kill = c2->take_damage(c1->get_damage());
        cout << c1->get_species() << " hitpoints: " << c1->get_hitpoints() << endl << c2->get_species() << " hitpoints: " << c2->get_hitpoints() << endl;
    }
    c2->die();
    add_money(c1->get_winnings(c2->get_payoff()));
    remove_dead(c2);
}
