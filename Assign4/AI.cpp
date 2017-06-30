#include "AI.h"

// Default Constructor
AI::AI() : Trainer(), rel_i(0), rel_j(0), pat_i(0), pat_j(0), last_move(4),
           expected_result(0), reversing(0), collect_pokeballs(1),
           found_poke_stop(0), collect_megastones(1), found_cave(0),
           ready_to_evolve(0), objectives_complete(0), moves{}, diverted(0),
           try_next(0), return_to_origin(1), going_right(1), down_count(2) {}

/*********************************************************************
** Function: AI::check_pokemon_need
** Description: Checks whether more of the Pokemon still need to be
**   caught to evolve to Stage 1.
** Parameters: int pkmn_number - the Pokemon's id number
** Pre-Conditions: pkmn_number is a valid Pokemon id number [1-6].
** Post-Conditions: N/A
** Return: True if the Pokemon is still needed, false otherwise.
*********************************************************************/
bool AI::check_pokemon_need(int pkmn_number) const {
    if (pkmn_number < 1 || pkmn_number > NUM_POKEMON)
        return false;
    int i;
    if (!find_pokemon(i, pkmn_number) || !pokemon[i]->get_stage())
        return true;
    return false;
}

/*********************************************************************
** Function: AI::check_all_stage1
** Description: Checks whether all Pokemon have been caught and evolved
**   to Stage 1.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: N/A
** Return: True if all 6 Pokemon are Stage 1.
*********************************************************************/
bool AI::check_all_stage1() const {
    int i = 0;
    bool stage1 = true;
    while (i < NUM_POKEMON && pokemon[i]) {
        if (!(stage1 = (pokemon[i++]->get_stage() == 1)))
            break;
    }
    return i == NUM_POKEMON && stage1;
}

/*********************************************************************
** Function: AI::reverse_move
** Description: Returns the opposite of the passed in move code.
** Parameters: int dir - the move number to reverse
** Pre-Conditions: dir is a valid move number [1-4].
** Post-Conditions: A notification has been printed to the console
**   for documentation purposes.
** Return: The oppose move number.
*********************************************************************/
int AI::reverse_move(int dir) const {
    cout << "reversing" << endl;
    switch (dir) {
        case 1: return 2;
        case 2: return 1;
        case 3: return 4;
        case 4: return 3;
    }
}

/*********************************************************************
** Function: AI::left_perpendicular
** Description: Returns the left-perpendicular of the passed in move code.
** Parameters: int dir - the move number to operate upon
** Pre-Conditions: dir is a valid move number [1-4].
** Post-Conditions: A notification has been printed to the console
**   for documentation purposes.
** Return: The left-perpendicular move number (i.e. up returns left,
**   down returns right).
*********************************************************************/
int AI::left_perpendicular(int dir) const {
    cout << "left-perpendicular" << endl;
    switch (dir) {
        case 1: return 3;
        case 2: return 4;
        case 3: return 2;
        case 4: return 1;
    }
}

/*********************************************************************
** Function: AI::right_perpendicular
** Description: Returns the right-perpendicular of the passed in move code.
** Parameters: int dir - the move number to operate upon
** Pre-Conditions: dir is a valid move number [1-4].
** Post-Conditions: A notification has been printed to the console
**   for documentation purposes.
** Return: The right-perpendicular move number (i.e. up returns right,
**   down returns left).
*********************************************************************/
int AI::right_perpendicular(int dir) const {
    cout << "right-perpendicular" << endl;
    switch (dir) {
        case 1: return 4;
        case 2: return 3;
        case 3: return 1;
        case 4: return 2;
    }
}

/*********************************************************************
** Function: AI::reset_results
** Description: Resets the try_next and expected_result variables to 0.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: try_next and expected_result have been reset to 0.
** Return: N/A
*********************************************************************/
void AI::reset_results() {
    try_next = 0;
    expected_result = 0;
}

/*********************************************************************
** Function: AI::load_edges
** Description: Unloads the information from the tuple array into a
**   2 x 2 integer array for easier access.
** Parameters: tuple<bool, int, string> move_choices[] - a four element
**               tuple array containing adjacent Location information
** Pre-Conditions: move_choices contains information from the Locations
**   adjacent to the current Location on the grid.
** Post-Conditions: The information from move_choices has been unloaded
**   into the 2 x 2 member array.
** Return: N/A
*********************************************************************/
void AI::load_edges(tuple<bool, int, string> move_choices[]) {
    for (int i = 0; i < 4; ++i) {
        if (get<0>(move_choices[i])) {
            if (!get<1>(move_choices[i]))
                set_move(i + 1, -1);
            else set_move(i + 1, get<1>(move_choices[i]));
        }
        else set_move(i + 1, 0);
    }
}

/*********************************************************************
** Function: AI::set_move
** Description: Updated the appropriate element of the 2 x 2 moves array.
** Parameters: int direction - the move number
**             int result - the value to store
** Pre-Conditions: N/A
** Post-Conditions: The appropriate element of the 2 x 2 moves array
**   have been updated.
** Return: N/A
*********************************************************************/
void AI::set_move(int direction, int result) {
    if (direction == 1)
        moves[0][0] = result;
    else if (direction == 2)
        moves[0][1] = result;
    else if (direction == 3)
        moves[1][0] = result;
    else moves[1][1] = result;
}

/*********************************************************************
** Function: AI::check_move
** Description: Retrieves the value stored in the appropriate element
**   of the moves array.
** Parameters: int direction - the move number
** Pre-Conditions: N/A (moves is a static array, so it cannot be null)
** Post-Conditions: N/A
** Return: The value stored in the appropriate element of the moves array.
*********************************************************************/
int AI::check_move(int direction) const {
    if (direction == 1)
        return moves[0][0];
    if (direction == 2)
        return moves[0][1];
    if (direction == 3)
        return moves[1][0];
    else return moves[1][1];
}

/*********************************************************************
** Function: AI::try_next_direction
** Description: When searching for a particular Event, tracks which
**   directions have been tried already and returns the next move to try.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: try_next has been incremented. If try_next was
**   incremented to 4, diverted set to false, reset_results() called,
**   and possible side effects from calling continue_pattern().
** Return: The determined move number
*********************************************************************/
int AI::try_next_direction() {
    ++try_next;
    int d;

    if (try_next == 1) {
        if (check_move(d = move_relations(1)))
            return d;
        ++try_next;
    }
    if (try_next == 2) {
        if (check_move(d = move_relations(2)))
            return d;
        ++try_next;
    }
    if (try_next == 3)
        if (check_move(d = move_relations(3)))
            return d;

    diverted = false;
    reset_results();
    return continue_pattern();

}

/*********************************************************************
** Function: AI::return_to_prof
** Description: Determines a move to bring the player closer to Professor
**   Oak to end the game.
** Parameters: N/A
** Pre-Conditions: objectives_complete is true.
** Post-Conditions: N/A
** Return: The move number to head towards Professor Oak
*********************************************************************/
int AI::return_to_prof() const {
    if (rel_i > 0)
        return 1;
    else if (rel_i < 0)
        return 2;
    else if (rel_j > 0)
        return 3;
    else return 4;
}

/*********************************************************************
** Function: AI::return_to_pattern
** Description: Determines a move to return the player to the Location
**   where their attention was diverted from the pattern. If the player
**   is already at that Location, calls refocus after setting diverted
**   to false if the Event that caused the diversion has already been found.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: If the player is already at the pattern, refocus has
**   been called, after resetting diverted to false if expected_result is 0.
** Return: The move number to return to the Location where the diversion
**   occurred, or the result of the call to refocus.
*********************************************************************/
int AI::return_to_pattern() {
    cout << "return to pattern" << endl;
    if (rel_i - pat_i > 0)
        return 1;
    else if (rel_i - pat_i < 0)
        return 2;
    else if (rel_j - pat_j > 0)
        return 3;
    else if (rel_j - pat_j < 0)
        return 4;
    else {
        if (!expected_result)
            diverted = false;
        return refocus();
    }
}

/*********************************************************************
** Function: AI::find_origin
** Description: Determines a move to bring the player towards the
**   upper left corner of the grid (where i and j are 0). If the origin
**   has been reached, resets return_origin_to false, sets going_right to
**   true and down_count to 2, and moves to the right.
** Parameters:
** Pre-Conditions: N/A
** Post-Conditions: If movement up and left are both not possible,
**   return_to_origin has been reset, going_right and down_count have been set.
** Return: The move number to bring the player towards the origin, or
**   to the right if the origin has been reached.
*********************************************************************/
int AI::find_origin() {
    if (check_move(3))
        return 3;
    if (check_move(1))
        return 1;
    return_to_origin = false;
    going_right = true;
    down_count = 2;
    return 4;
}

/*********************************************************************
** Function: AI::set_diversion
** Description: Sets diverted to true, and assigns the current row and
**   column to the row and column to return to once the diversion has
**   been resolved.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Diverted is true, and pat_i and pat_j are equal to
**   rel_i and rel_j, respectively.
** Return: N/A
*********************************************************************/
void AI::set_diversion() {
    diverted = true;
    pat_i = rel_i;
    pat_j = rel_j;
}

/*********************************************************************
** Function: AI::refocus
** Description: Looks for a useful Event if none is currently being
**   searched for. If an Event is being looked for (even if it has just
**   been identified), calls try_next_direction(). Otherwise, calls
**   continue_pattern().
** Parameters: N/A
** Pre-Conditions: pat_i == rel_i and pat_j == rel_j (i.e. this is the
**   Location of the last diversion, which may have been identified in
**   this function call).
** Post-Conditions: Possible new expected_result and diverted values
**   from get_new_target() call. Possible side effects from try_next_direction
**   or continue_pattern() calls.
** Return: The determined move number.
*********************************************************************/
int AI::refocus() {
    cout << "refocus" << endl;
    if (!expected_result)
        get_new_target();
    if (expected_result)
        return try_next_direction();
    else return continue_pattern();
}

/*********************************************************************
** Function: AI::continue_pattern
** Description: When no useful Event is adjacent to the player, this
**   function is used to move the player in a zig-zag pattern to ensure
**   that no areas of the map are neglected.
** Parameters: bool check_not_move - this function is called from
**               move_relations for use in try_new_direction, but does
**               not progress the pattern forward. If this Boolean is
**               true, certain side effects within this function are
**               prevented to ensure that the proper pattern is followed
**               when this function is called for its primary purpose.
** Pre-Conditions: N/A
** Post-Conditions: return_to_origin, going_right, and down_count have
**   been updated (if necessary) to reflect the current position in the
**   pattern and Location on the grid. Text notifications have been
**   printed to the console regarding the pattern's state.
** Return: The determined move number to continue the pattern.
*********************************************************************/
int AI::continue_pattern(bool check_not_move) {
    if (!check_not_move)
        cout << "continuing pattern" << endl;
    if (!check_move(4) && !check_move(2)) {
        return_to_origin = true;
        cout << "returning to origin" << endl;
    }
    if (return_to_origin)
        return find_origin();

    if (going_right) {
        if (check_move(4)) {
            cout << "Going right still" << endl;
            return 4;
        }
        else if (down_count) {
            if (!check_not_move) {
                --down_count;
                cout << "Going down " << down_count << endl;
            }
            return 2;
        }
        else {
            down_count = 2;
            going_right = false;
            cout << "Going left now" << endl;
            return 3;
        }
    }
    else {
        if (check_move(3)) {
            cout << "Going left still" << endl;
            return 3;
        }
        else if (down_count && check_move(2)) {
            if (!check_not_move) {
                --down_count;
                cout << "Going down " << down_count << endl;
            }
            return 2;
        }
        else {
            down_count = 2;
            going_right = true;
            cout << "Going right now" << endl;
            return 4;
        }
    }
}

/*********************************************************************
** Function: AI::move_relations
** Description: Reverses, takes the left- or right-perpendicular of the
**   next move that will be executed in the pattern.
** Parameters: int relation - a code for the operation to perform
** Pre-Conditions: N/A
** Post-Conditions: N/A (continue_pattern() side effects are suppressed)
** Return: The move determined by the indicated operation on the next
**   move that will be executed in the pattern.
*********************************************************************/
int AI::move_relations(int relation) {
    if (relation == 1)
        return reverse_move(continue_pattern(true));
    if (relation == 2)
        return left_perpendicular(continue_pattern(true));
    if (relation == 3)
        return right_perpendicular(continue_pattern(true));
}

/*********************************************************************
** Function: AI::update_rel_coords
** Description: Updates the internal coordinates relative to the start
**   location (Professor Oak).
** Parameters: int decision
** Pre-Conditions: N/A
** Post-Conditions: rel_i and rel_j have been updated to reflect the
**   latest move.
** Return: N/A
*********************************************************************/
void AI::update_rel_coords(int decision) {
    if (decision == 1)      // Up
        --rel_i;
    else if (decision == 2) // Down
        ++rel_i;
    else if (decision == 3) // Left
        --rel_j;
    else ++rel_j;           // Right

    last_move = decision;
}

/*********************************************************************
** Function: AI::get_new_target
** Description: Looks for useful Events adjacent to the current Location,
**   prioritizing Poke-stops (if not already found), then Caves (if not
**   already found), then Pokemon that are still needed for Stage 1. If
**   found, calls set_diversion() and sets the expected_result based on the
**   useful Event's code.
** Parameters: N/A
** Pre-Conditions: expected_result is 0.
** Post-Conditions: If a useful Event has been identified, set_diversion()
**   has been called, and the Event's code has been stored in expected_result.
** Return: N/A
*********************************************************************/
void AI::get_new_target() {
    cout << "get new target" << endl;
    if (collect_pokeballs)
        for (int i = 0; i < 4; ++i)
            if(check_move(i + 1) == 8) {
                expected_result = 8;
                set_diversion();
                break;
            }
    if (!expected_result && collect_megastones)
        for (int i = 0; i < 4; ++i)
            if(check_move(i + 1) == 7) {
                expected_result = 7;
                set_diversion();
                break;
            }
    if (!expected_result && !collect_pokeballs)
        for (int i = 0; i < 4; ++i)
            if(check_move(i + 1) > 0 && check_pokemon_need(check_move(i + 1))) {
                expected_result = check_move(i + 1);
                set_diversion();
                break;
            }
}

/*********************************************************************
** Function: AI::decide_move
** Description: Determines the next move to be made, based on which
**   objectives have been completed and the adjacent Event percepts.
** Parameters: tuple<bool, int, string> move_choices[] - a four element
**               static tuple array
** Pre-Conditions: N/A
** Post-Conditions: Various side-effects possible depending on conditional
**   logic. The relative coordinates have been updated, and the move
**   options and choice have been documented in the console.
** Return: The determined move number.
*********************************************************************/
int AI::decide_move(tuple<bool, int, string> move_choices[]) {
    int decision = 0;
    load_edges(move_choices);

    if (objectives_complete)
        decision = return_to_prof();
    else if (ready_to_evolve && !collect_megastones)
        decision = 5;
    else if ((collect_pokeballs && found_poke_stop)
          || (collect_megastones && found_cave))
        decision = reverse_move(last_move);
    else if (diverted)
        decision = return_to_pattern();
    else decision = refocus();

    update_rel_coords(decision);
    cout << get_move_prompt(move_choices) << decision << endl;
    return decision;
}

/*********************************************************************
** Function: AI::decide_throw_pokeball
** Description: Decides whether to use a pokeball to attempt to catch
**   the Pokemon.
** Parameters: Pokemon *pkmn - the encountered Pokemon
** Pre-Conditions: pkmn is not a null pointer.
** Post-Conditions: N/A
** Return: 1 to attempt to catch the Pokemon, 2 to pass on the chance.
*********************************************************************/
int AI::decide_throw_pokeball(Pokemon *pkmn) {
    int throw_ball;
    if (objectives_complete)
        throw_ball = 2;
    else if (check_pokemon_need(pkmn->get_number()))
        throw_ball = 1;
    else throw_ball = 2;
    cout << "Throw a pokeball at " + pkmn->get_name() + "? (1 - yes, 2 - no) " << throw_ball << endl;
    return throw_ball;
}

/*********************************************************************
** Function: AI::manage_inventory
** Description: Once all Pokemon have been caught and raised to Stage 1
**   and enough megastones have been collected, this function is called
**   to evolve all Pokemon to Stage 2 and set objectives_complete to true,
**   indicating it is time to return to Professor Oak.
** Parameters: N/A
** Pre-Conditions: All Pokemon have been caught and raised to Stage 1,
**   and enough megastones have been collected to evolve all Pokemon.
** Post-Conditions: All Pokemon are now Stage 2, and objectives_complete
**   is true.
** Return: N/A
*********************************************************************/
void AI::manage_inventory() {
    for (int i = 0; i < NUM_POKEMON; ++i) {
        print_inventory();
        cout << "1. Evolve a Pokemon to Stage 2.\n2. Exit.\n\n1\n"
             << "Choose a Pokemon to evolve: " << i + 1 << endl;
        pokemon[i]->evolve();
        --megastones;
    }
    print_inventory();
    cout << "1. Evolve a Pokemon to Stage 2.\n2. Exit.\n\n2\n";
    objectives_complete = true;
}

/*********************************************************************
** Function: AI::log_event
** Description: Evaluates the event code of the event that was at the
**   current Location. If it is a Poke-stop or a Cave, found_poke_stop
**   or found_cave are set to true, respectively. If the event_result is
**   equal to the expected result, reset_results() is called.
** Parameters: int event_result - the code returned by the event
** Pre-Conditions: event_result is the event code of the Event that
**   was at the current Location (it may have been moved by now).
** Post-Conditions: found_poke_stop and found_cave have been set to
**   true, if applicable. If event_result == expected_result, reset_results()
**   has been called.
** Return: N/A
*********************************************************************/
void AI::log_event(int event_result) {
    if (event_result == 8)
        found_poke_stop = true;
    else if (event_result == 7)
        found_cave = true;

    if (event_result == expected_result)
        reset_results();
}

/*********************************************************************
** Function: AI::add_megastone
** Description: Increments megastones and turns off collect_megastones
**   if a sufficient number have been collected.
** Parameters: N/A
** Pre-Conditions: The player moved to a Location with a Cave.
** Post-Conditions: megastones has been incremented, and collect_megastones
**   has been turned off if a sufficient number have been collected.
** Return: N/A
*********************************************************************/
void AI::add_megastone() {
    ++megastones;
    if (collect_megastones && megastones >= NUM_POKEMON) {
        collect_megastones = false;
        cout << "Done collecting megastones." << endl;
    }
}

/*********************************************************************
** Function: AI::add_pokeballs
** Description: Adds pokeballs and turns off collect_pokeballs if a
**   sufficient number have been collected.
** Parameters: int num - the number to add
** Pre-Conditions: The player moved to a Location with a Poke-stop.
** Post-Conditions: pokeballs has been increased by num, and collect_pokeballs
**   has been turned off if a sufficient number have been collected.
** Return: N/A
*********************************************************************/
void AI::add_pokeballs(int num) {
    pokeballs += num;
    if (collect_pokeballs && pokeballs >= NUM_POKEMON * MAX_EVOLVE_NUM * 8) { // 2x bad luck factor
        collect_pokeballs = false;
        cout << "Done collecting pokeballs." << endl;
    }
}

/*********************************************************************
** Function: AI::use_pokeball
** Description:
** Parameters: N/A
** Pre-Conditions:
** Post-Conditions:
** Return: N/A
*********************************************************************/
void AI::use_pokeball() {
    --pokeballs;
    if (!pokeballs) {
        collect_pokeballs = true;
        found_poke_stop = false;
    }
}

/*********************************************************************
** Function: AI::catch_pokemon
** Description: If the Pokemon has been previously caught, it is found
**   in the pokemon array, and the add_caught() member is called. Otherwise,
**   pkmn is cloned and assigned to the first empty element of pokemon array.
**   If all Pokemon are now Stage 1, ready_to_evolve is set to true.
** Parameters: Pokemon *pkmn - the pokemon that has been caught
** Pre-Conditions: pkmn has been caught.
** Post-Conditions: The pokemon array has been updated to reflect pkmn being
**   caught, and ready_to_evolve is set to true, if applicable.
** Return: N/A
*********************************************************************/
void AI::catch_pokemon(Pokemon *pkmn) {
    int i;
    if (!find_pokemon(i, pkmn->get_number()))
        pokemon[i] = pkmn->clone();
    pokemon[i]->add_caught();
    if (!ready_to_evolve && check_all_stage1())
        ready_to_evolve = true;
}
