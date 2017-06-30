/******************************************************
** Program: driver.cpp
** Author: Thomas Hollenberg
** Date: 05/07/2017
** Description: Runs a text-based fantasy role-playing
**   game.
** Input: The user must input numbers to control program
**   flow.
** Output: Prints the results of in-game actions as they
**   occur.
******************************************************/

#include "Game.h"

/*********************************************************************
** Function: main
** Description: Welcomes the user to Gladiator Coliseum Tycoon, and
**   allows them to start a new game or quit. Creates a new Game
**   object and calls Game::play() if the user chooses to start a new
**   game.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The user chose to quit.
** Return: 0
*********************************************************************/
int main() {
    srand(time(0));

    cout << "Welcome to Gladiator Coliseum Tycoon!\n" << endl;

    int play_quit = -1;
    get_pos_integer("1. Start a new game\n2. Quit\n\n", &play_quit, 2);
    while (play_quit != 2) {
        Game g;
        g.play();
        get_pos_integer("1. Start a new game\n2. Quit\n\n", &play_quit, 2);
    }

    return 0;
}
