#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

using namespace std;

bool is_int(string);
int get_int(int, int, string);

bool is_float(string);
float get_float(float, float, string);

string get_string(int, string);
int menu(int min, int max, string message);

char game_menu(string, string);

#endif
