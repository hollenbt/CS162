#ifndef VALIDATION_LIBRARY_H_INCLUDED
#define VALIDATION_LIBRARY_H_INCLUDED

#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;

void check_file(ifstream&, const string&);
void check_file(ofstream&, const string&);
void get_pos_integer(const string&, int*, int max_input = numeric_limits<int>::max());
void get_nonneg_integer(const string&, int*, int max_input = numeric_limits<int>::max());
void get_pos_double(const string&, double*, double max_input = numeric_limits<double>::max());
void get_nonneg_double(const string&, double*, double max_input = numeric_limits<double>::max());
void get_integer_string(const string&, string&);
bool check_24hr_no_colon_time_string(const string&);


#endif // VALIDATION_LIBRARY_H_INCLUDED
