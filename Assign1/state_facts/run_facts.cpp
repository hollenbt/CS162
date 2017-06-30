/******************************************************
** Program: run_facts.cpp
** Author: Thomas Hollenberg
** Date: 04/09/2017
** Description: Reads in state and county data from a
**   file, analyzes the data, and prints a report to a
**   file or to the console.
** Input: The filename to read data from, and the number
**   of states with data present in the file.
** Output: States and their counties sorted by population,
**   states and their counties sorted alphabetically, the
**   state with the largest population, the county with
**   the largest population, all counties with average
**   income over a user-specified amount, the population-
**   weighted average house price for each state.
******************************************************/

#include "./state_facts.h"

/*********************************************************************
** Function: main
** Description: Checks command-line arguments, then reads in data,
**   conducts the analysis, prints the results. Prompts the user
**   for new data files to analyze until they choose to exit.
** Parameters: int argc - the number of command-line arguments.
**             char *argv[] - the c-style string array of command-line
**               arguments.
** Pre-Conditions: N/A
** Post-Conditions: Analysis has been conducted and printed to a file or
**   the console.
** Return: 1 if invalid command-line arguments were passed in, 0 otherwise.
*********************************************************************/
int main(int argc, char *argv[]) {
    if (!is_valid_arguments(argv, argc))
        return 1;

    int num_states = atoi(argv[2]);
    string filename = string(argv[4]);
    bool again = true;
    state *data;

    while (again) {
        ifstream input;
        open_input_file(filename, input);
        collect_data(&data, num_states, input);
        conduct_analysis(data, num_states);
        delete_info(&data, num_states);
        prompt_repeat(again, num_states, filename);
    }

    return 0;
}
