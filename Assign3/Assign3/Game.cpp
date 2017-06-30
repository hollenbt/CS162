#include "Game.h"

// Default Constructor
Game::Game() : w(), username(), gold_invested(0) {}

/*********************************************************************
** Function: Game::play
** Description: Gets the user's name and calls Game::menu() to start
**   the game.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The game has been played.
** Return: N/A
*********************************************************************/
void Game::play() {
    cout << "\nPlease enter your name: ";
    getline(cin, username);
    menu();
}

/*********************************************************************
** Function: Game::menu
** Description: Allows the user to invest money, recruit gladiators,
**   and hold tournaments until they choose to sell their assets.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The user has chosen to sell their assets and end
**   the game.
** Return: N/A
*********************************************************************/
void Game::menu() {
    string options = "\nKing " + username + ", what is your next command?\n\t1. Begin tournament.\n\t2. View/Recruit gladiators.\n\t3. Invest money.\n\t4. Sell assets.\n\n";
    int choice = -1;
    do {
        get_pos_integer(options, &choice, 5);
        if (choice == 1) {
            if (w.get_num_creatures() < 2)
                cout << "\nYou need to recruit gladiators first.\n";
            else start_tournament();
        }
        else if (choice == 2)
            buy_creatures();
        else if (choice == 3)
            add_money();
        else if (choice == 4)
            summarize();
    } while (choice != 4);
}

/*********************************************************************
** Function: Game::buy_creatures
** Description: Allows the user to view their stable of gladiators and
**   recruit additional Creatures is they have enough gold.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Any purchased Creatures have been added to w and
**   their cost has been deducted from w.bank and added to w.g_spent.
** Return: N/A
*********************************************************************/
void Game::buy_creatures() {
    int choice = -1, num;
    string menu = "Recruit:\n\t1. Humans (10 gold).\n\t2. High Elves (12 gold).\n\t3. Dryads (15 gold).\n\t4. Balrogs (20 gold).\n\t5. Cyberdemons (20 gold).\n\t6. Done.\n\n";
    while (choice != 6) {
        w.display_creatures();
        cout << '\n' << w.get_bank() << " gold available." << endl;
        get_pos_integer(menu, &choice, 6);
        if (choice != 6) {
            get_pos_integer("How many? ", &num);
            if (choice == 1)
                w.add_humans(num);
            else if (choice == 2)
                w.add_high_elves(num);
            else if (choice == 3)
                w.add_dryads(num);
            else if (choice == 4)
                w.add_balrogs(num);
            else if (choice == 5)
                w.add_cdemons(num);
        }
    }
}

/*********************************************************************
** Function: Game::add_money
** Description: Allows the user to invest money, adding it to their gold
**   total. The user is facetiously prompted for their credit card
**   information, but it is not stored and any input will be accepted.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: They invested money has been added to gold_invested
**   and w.bank.
** Return: N/A
*********************************************************************/
void Game::add_money() {
    double investment = -1;
    get_nonneg_double("\nHow much money would you like to invest? ", &investment);
    string s;
    cout << "Credit card number: ";
    getline(cin, s);
    cout << "Expiration Date (MM/YYYY): ";
    getline(cin, s);
    cout << "CVV code: ";
    getline(cin, s);
    w.add_money(investment);
    gold_invested += investment;
}

/*********************************************************************
** Function: Game::start_tournament
** Description: Conducts a gladiator tournament, prompting the user to
**   choose pairs of combatants to duel until only one remains alive.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: All but one Creature in w has been killed. The
**   earnings have been added to w.bank and w.g_earned.
** Return: N/A
*********************************************************************/
void Game::start_tournament() {
    cout << "\nWhat a beautiful day for some carnage! The public agrees; the coliseum is packed.\n";
    int i1, i2;
    Creature *c1, *c2;
    while (w.get_num_creatures() > 1) {
        w.display_creatures();
        cout << "\nPick a pair of combatants.\n";
        get_pos_integer("First combatant number: ", &i1, w.get_num_creatures());
        get_pos_integer("Second combatant number: ", &i2, w.get_num_creatures());
        if (i1 == i2) {
            cout << "A gladiator cannot fight itself!" << endl;
            continue;
        }

        c1 = w.get_creature(i1 - 1);
        c2 = w.get_creature(i2 - 1);
        w.battle(c1, c2);
        cout << "The crowd goes wild!" << endl;
    }
}

/*********************************************************************
** Function: Game::summarize
** Description: Prints a summary of the user's game performance, including
**   cumulative gold invested, spent on gladiators, and earned from payoffs.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The user's game performance stats have been printed.
** Return: N/A
*********************************************************************/
void Game::summarize() const {
    cout << "\nKing " << username << ", you:\n\tinvested " << gold_invested << " gold,\n\tspent "
         << w.get_gold_spent() << " gold, and\n\tearned " << w.get_gold_earned() - gold_invested << " gold,\n\tallowing"
         << " you to sell the coliseum\n\tat a valuation of " << w.get_bank() << " gold\n\tfor a "
         << w.get_gold_earned() - w.get_gold_spent() - gold_invested << " gold profit.\n\n";
}
