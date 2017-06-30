#include "Game_World.h"

// Non-default Constructor
Game_World::Game_World(int len, int wid, int max_abu) : length(len), width(wid),
                                           grid(new Location*[length]),
                                           curr_i(0), curr_j(0),
                                           max_abundance(max_abu),
                                           num_blank(length * width - 1 - ((((length * width - 1) / (NUM_POKEMON + 2) < max_abu) ? (length * width - 1) / (NUM_POKEMON + 2) : max_abu) * (NUM_POKEMON + 2))),
                                           blank(new Location*[num_blank]{}) {

    for (int i = 0; i < length; ++i)
        grid[i] = new Location[width];
}

// Destructor
Game_World::~Game_World() {
    for (int i = 0; i < length; ++i)
        delete[] grid[i];
    delete[] grid;
    delete[] blank;
}

/*********************************************************************
** Function: Game_World::create_event
** Description: Creates a new Event-derived object based on the passed
**   in string. If the Prof object is created, the player's starting
**   Location is set. If a Blank object is created, the address of the
**   Location to which it will be assigned is added to the blank array.
** Parameters: const string &event_name - the name of the event
**             int i - the row of the Location to which it will be assigned
**             int j - the column of the Location to which it will be assigned
** Pre-Conditions: i and j are valid grid indices
** Post-Conditions: A new Event-derived object has been created, and
**   starting or blank Locations have been set, if applicable.
** Return: A pointer to the newly created Event.
*********************************************************************/
Event* Game_World::create_event(const string &event_name, int i, int j) {
    if (!event_name.compare("Prof")) {
        curr_i = i;
        curr_j = j;
        return new Prof;
    }
    if (!event_name.compare("Cave"))
        return new Cave;
    if (!event_name.compare("Poke_stop"))
        return new Poke_stop;
    if (!event_name.compare("Charizard"))
        return new Charizard;
    if (!event_name.compare("Espeon"))
        return new Espeon;
    if (!event_name.compare("Geodude"))
        return new Geodude;
    if (!event_name.compare("Mewtwo"))
        return new Mewtwo;
    if (!event_name.compare("Onix"))
        return new Onix;
    if (!event_name.compare("Rayquaza"))
        return new Rayquaza;

    Blank *b = new Blank;
    int x = 0;
    while (blank[x])
        ++x;
    blank[x] = &grid[i][j];
    return b;
}

/*********************************************************************
** Function: Game_World::move_event
** Description: Swaps the event of the passed in Location address with
**   a random one of the Blank events in the blank array (if any).
**   Updates the blank array with the new Blank Location address.
** Parameters: Location *old - Location to swap event member with a Blank
** Pre-Conditions: old points to a Location object that contains a
**   Pokemon-derived event member
** Post-Conditions: The event has been swapped with a Blank (if any exist),
**   and the blank array has been updated with the Location address.
** Return: N/A
*********************************************************************/
void Game_World::move_event(Location *old) {
    if (!num_blank)
        return;
    int new_loc = rand() % num_blank;
    Event* temp = blank[new_loc]->get_event();
    blank[new_loc]->set_event(old->get_event());
    old->set_event(temp);
    blank[new_loc] = old;
}

/*********************************************************************
** Function: Game_World::get_move_choices
** Description: Populates the tuple array with information about the
**   adjacent grid Locations (including whether or not they exist, the
**   percept code - for AI, and the direction string - for DEBUG mode
**   printout).
** Parameters: tuple<bool, int, string> move_choices[] - a four element
**               static tuple array
** Pre-Conditions: The tuple array has been initialized with false values
**   so values must only be updated with the grid Location exists.
** Post-Conditions: The tuple array has been loaded with adjacent grid
**   Location information.
** Return: N/A
*********************************************************************/
void Game_World::get_move_choices(tuple<bool, int, string> move_choices[]) {
    if (curr_i) {
        #ifdef DEBUG
            cout << "\nUp: ";
        #endif // DEBUG
        get<1>(move_choices[0]) = grid[curr_i - 1][curr_j].get_event()->percept();
        get<0>(move_choices[0]) = true;
    }
    if (curr_i != length - 1) {
        #ifdef DEBUG
            cout << "\nDown: ";
        #endif // DEBUG
        get<1>(move_choices[1]) = grid[curr_i + 1][curr_j].get_event()->percept();
        get<0>(move_choices[1]) = true;
    }
    if (curr_j) {
        #ifdef DEBUG
            cout << "\nLeft: ";
        #endif // DEBUG
        get<1>(move_choices[2]) = grid[curr_i][curr_j - 1].get_event()->percept();
        get<0>(move_choices[2]) = true;
    }
    if (curr_j != width - 1) {
        #ifdef DEBUG
            cout << "\nRight: ";
        #endif // DEBUG
        get<1>(move_choices[3]) = grid[curr_i][curr_j + 1].get_event()->percept();
        get<0>(move_choices[3]) = true;
    }
}

/*********************************************************************
** Function: Game_World::make_move
** Description: Updates the row and column of the player's current
**   Location based on the chosen move.
** Parameters: int choice - the move code
** Pre-Conditions: choice is on 1 to 4 inclusive
** Post-Conditions: The current Location indices have been updated
** Return: N/A
*********************************************************************/
void Game_World::make_move(int choice) {
    if (choice == 1) // Up
        --curr_i;
    else if (choice == 2) // Down
        ++curr_i;
    else if (choice == 3) // Left
        --curr_j;
    else if (choice == 4) // Right
        ++curr_j;
    else cout << "Invalid move selection.\n";
}

/*********************************************************************
** Function: Game_World::initialize
** Description: Determines how many of each derived Event object there
**   will be and randomly assigns them to grid Locations.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: All grid Locations have been assigned a dynamically
**   allocated Event-derived object.
** Return: N/A
*********************************************************************/
void Game_World::initialize() {
    int quant = ((length * width - 1) / (NUM_POKEMON + 2) < max_abundance) ? (length * width - 1) / (NUM_POKEMON + 2) : max_abundance;
    int num;
    vector<pair<string, int>> event_list {{"Prof", 1}, {"Cave", quant}, {"Poke_stop", quant},
                    {"Charizard", quant}, {"Espeon", quant}, {"Geodude", quant}, {"Mewtwo", quant},
                    {"Onix", quant}, {"Rayquaza", quant}};

    if (num_blank)
        event_list.emplace_back("Event", num_blank);

    int num_events = length * width;
    for (int i = 0; i < length; ++i)
        for (int j = 0; j < width; ++j) {
            num = rand() % num_events--;
            int ele = 0;
            auto it = event_list.begin();
            while (num > (it + ele)->second - 1)
                num -= (it + ele++)->second;
            grid[i][j].set_event(create_event((it + ele)->first, i, j));
            --(it + ele)->second;
            if (!(it + ele)->second)
                event_list.erase(it + ele);
        }
}

/*********************************************************************
** Function: Game_World::print_map
** Description: Prints a visualization of the grid, based on the event
**   codes of each Location.
** Parameters: N/A
** Pre-Conditions: The grid has been initialized previously.
** Post-Conditions: The map has been printed.
** Return: N/A
*********************************************************************/
void Game_World::print_map() const {
    cout << "\n\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == curr_i && j == curr_j) {
                cout << '|' << grid[i][j].get_event()->get_code() << '|';
            }
            else cout << ' ' << grid[i][j].get_event()->get_code() << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

/*********************************************************************
** Function: Game_World::play
** Description: Creates a new Trainer or AI and starts the game. Handles
**   deallocation after the game is finished as well.
** Parameters: bool real_player - true if the user wants to play, false
**               if the AI will take over
** Pre-Conditions: The grid has been initialized.
** Post-Conditions: The game has been played to completion, and the
**   dynamic memory has been deallocated.
** Return: N/A
*********************************************************************/
void Game_World::play(bool real_player) {
    if (real_player) {
        Trainer *trainer = new Trainer;
        play_game(trainer, true);
        delete trainer;
    }
    else {
        AI *ai = new AI;
        play_game(ai, false);
        delete ai;
    }
}

/*********************************************************************
** Function: Game_World::play_game
** Description: Conducts gameplay, prompting the player (whether it be
**   a human or AI) to make decisions. If in DEBUG mode, prints the map
**   before each turn. Tracks the number of turns to finish the game.
** Parameters: Trainer *trainer - polymorphic Trainer pointer to a
**               Trainer or AI object
** Pre-Conditions: The grid has been initialized, trainer is not a null
**   pointer.
** Post-Conditions: The game has been finished and the number of turns
**   has been printed.
** Return: N/A
*********************************************************************/
void Game_World::play_game(Trainer *trainer, bool real_player) {
    cout << "\nHello there! Welcome to the world of Pokemon! My name is Oak! People call me the Pokemon Prof!\n"
         << "This world is inhabited by creatures called Pokemon! Use pokeballs from the Poke-stop to catch\n"
         << "enough of them to evolve to Stage 1, and use megastones to evolve to Stage 2. I've seen some\n"
         << "lying around in caves. Return to me when you've caught and raised all the Pokemon to Stage 2!" << endl;

    string s;
    int event_result = 0, choice, num_moves = 0;
    while (event_result != -1) {
        tuple<bool, int, string> move_choices[4] {make_tuple(false, 0, "Up"), make_tuple(false, 0, "Down"),
                                                  make_tuple(false, 0, "Left"), make_tuple(false, 0, "Right")};
        get_move_choices(move_choices);

        #ifdef DEBUG
            print_map();
        #else
            cout << "\n\n";
        #endif // DEBUG

        choice = trainer->decide_move(move_choices);

        if (choice == 5)
            trainer->manage_inventory();
        else {
            make_move(choice);
            event_result = grid[curr_i][curr_j].get_event()->perform_event(*trainer);
            trainer->log_event(event_result);
            if (event_result > 0 && event_result < 7)
                move_event(&grid[curr_i][curr_j]);
        }

        ++num_moves;
        if (!real_player && s.compare("run"))
            getline(cin, s);
    }
    cout << "You won in " << num_moves << " moves." << endl;
}
