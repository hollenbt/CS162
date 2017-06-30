/*********************************************************************
** Program Filename: Pokemon_Go
** Author: Tommy Hollenberg
** Date: 05/24/2017
** Description: A text-based variation of the popular cell phone game
**   Pokemon Go. The player must acquire pokeballs from Poke-stops,
**   catch the required number of each Pokemon to evolve them all to
**   Stage 1, and find megastones in caves to evolve them all to Stage
**   2, before returning to Professor Oak at the starting location to
**   end the game. There is also an AI that plays the game by itself.
**   In DEBUG mode, the directions of the each event are divulged, and
**   the map is displayed on the screen. DEBUG mode does not change the
**   AI strategy.
** Input: Three integers must be passed in as command-line arguments:
**           -- game grid length (>= 3)
**           -- game grid width (>= 3)
**           -- maximum abundance of each event (>= 1)
**        Professor Oak always occurs only once. All others are split
**        evenly among the remaining squares, unless bounded by the
**        maximum abundance value. Blank events fill the remainder of
**        the grid.
** Output: Textual game narration, as well as a map in DEBUG mode.
*********************************************************************/

#include "Game_World.h"
#include <cstring>

/*********************************************************************
** Function: check_args
** Description: Converts the command-line arguments to integers and
**   verifies that they are valid.
** Parameters: int argc - argument count
**             char *argv[] - array of c-style string arguments
**             int &length - to store the grid length
**             int &width - to store the grid width
**             int &max_abu - to store the maximum event abundance
** Pre-Conditions: argc is the number of elements of argv
** Post-Conditions: the second, third, and fourth c-style strings in
**   argv have been converted to integers and stored in length,
**   width, and max_abu, respectively.
** Return: true if length and width are >= 3 and max_abu >= 1, false
**   otherwise.
*********************************************************************/
bool check_args(int argc, char *argv[], int &length, int &width, int &max_abu) {
    if (argc != 4)
        return false;
    for (int a = 1; a < argc; ++a)
        for (int i = 0; i < strlen(argv[a]); ++i)
            if (argv[a][i] < '0' || argv[a][i] > '9')
                return false;

    length = atoi(argv[1]);
    width = atoi(argv[2]);
    max_abu = atoi(argv[3]);
    return max_abu > 0 && length > 2 && width > 2;
}

/*********************************************************************
** Function: get_dimensions
** Description: Gets new values for grid length, width, and maximum
**   event abundance from the user.
** Parameters: int *length - to point to the length
**             int *width - to point to the width
**             int *max_abu - to point to the maximum abundance
** Pre-Conditions: length, width, and max_abu are not null pointers.
** Post-Conditions: length, width, and max_abu point to integers that
**   are >= 3, 3, and 1, respectively.
** Return: N/A
*********************************************************************/
void get_dimensions(int *length, int *width, int *max_abu) {
    do {
        get_pos_integer("Enter board length (must be >= 3): ", length);
        get_pos_integer("Enter board width (must be >= 3): ", width);
        get_pos_integer("Enter maximum event abundance (must be >= 1): ", max_abu);
    } while (*length < 3 || *width < 3);
}

/*********************************************************************
** Function: main
** Description: Checks command-line arguments. Lets the player choose
**   to play themselves or have the AI play (or quit the game). Then
**   creates and initializes a Game_World object, plays the game, and
**   lets the player choose to play again with the same board configuration
**   or create a fresh game. Loops until the player chooses to quit.
** Parameters: int argc - argument count
**             char *argv[] - c-style string arguments
** Pre-Conditions: N/A
** Post-Conditions: The user chose to quit. All dynamic memory has been
**   deallocated.
** Return: 1 if invalid command-line arguments, 0 otherwise.
*********************************************************************/
int main(int argc, char *argv[]) {
    srand(time(0));
    int length, width, max_abu;

    if (!check_args(argc, argv, length, width, max_abu)) {
        cout << "Invalid grid dimensions.\n" << endl;
        return 1;
    }

    int choice, rechoice;
    bool first = true;
    string init_prompt = "\n1. New game.\n2. New AI game.\n3. Quit.\n\n";
    string reprompt = "\n1. Play again.\n2. Quit to main menu.\n\n";

    while (1) {
        get_pos_integer(init_prompt, &choice, 3);
        if (choice == 3)
            break;
        if (!first)
            get_dimensions(&length, &width, &max_abu);

        Game_World new_game(length, width, max_abu);
        new_game.initialize();
        do {
            new_game.play(choice != 2);
            get_pos_integer(reprompt, &rechoice, 2);
        } while (rechoice == 1);
        first = false;
    }
    return 0;
}
