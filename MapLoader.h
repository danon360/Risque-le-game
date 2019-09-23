#pragma once
#include <iostream>;
#include <fstream>;
#include <sstream>;
#include <string>;
#include <algorithm>;
#include <vector>;

using namespace std;

//a temporary classes
class continent;
class country;


//function that when given a string loads the continents into a vector and returns it
vector<continent>* continentLoader(string input);

//function that when given a string loads the countries into a vector and return it
vector<country>* countryLoader(string input);

//function that accepts a string of borders as a parameters, goes through it, and adds the borders in the list
bool addBorders(string input, vector<country> country);

//trims any whitespace from both sides of the string 
string trim(string input);

