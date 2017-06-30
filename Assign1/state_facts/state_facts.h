#ifndef STATE_FACTS_H_INCLUDED
#define STATE_FACTS_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

struct county {
    string name;
    string *city;
    int cities;
    int population;
    float avg_income;
    float avg_house;
};

struct state {
    string name;
    county *c;
    int counties;
    int population;
};

bool is_valid_arguments(char*[], int);
state* create_states(int);
void get_state_data(state*, int, ifstream&);
county* create_counties(int);
void get_county_data(county*, int, ifstream&);
void delete_info(state**, int);

bool is_nonzero_pos_integer(const char*);
void open_input_file(string, ifstream&);
void collect_data(state**, int, ifstream&);
void prompt_repeat(bool&, int&, string&);
void conduct_analysis(state*, int);
void calc_and_output(state*, int, double, ostream&);
void output_pop(state**, int, ostream&);
void output_alpha(state**, int, ostream&);
void above_min_income(state**, int, double, ostream&);
void avg_house_by_state(state**, int, ostream&);

template<typename T>
void set_pointers(T***, T*, int);
template<typename T>
void merge(T*, int, int, int, bool (*comparisonFcn)(T, T));
template<typename T>
void iterativeMergeSort(T*, int, int, bool (*comparisonFcn)(T, T));
template<typename T>
bool sort_by_pop(T*, T*);
template<typename T>
bool sort_alphabetic(T*, T*);

#endif // STATE_FACTS_H_INCLUDED
