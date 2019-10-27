#pragma once
#include"Map.h";
#include <map>;
#include <regex>

using std::map;
using std::stringstream;
using std::ifstream;
using std::regex_match;

class MapLoader {
public:
	string* fileLocation;
	MapLoader();
	MapLoader(string location);
	Map* init();
	//function that takes a string containing the file location, and then procedes to load the file content into 3 seperate string pointers provided to it in the parameters
	bool loadFileToStrings(string* fileLocation, string* continent, string* country, string* borders);

	//function that when given a string loads the continents into a vector and returns it
	vector<Continent*>* continentLoader(string input);

	//function that when given a string loads the countries into a vector and return it
	map<int, Country*>* countryLoader(string input,vector<Continent*>* contVec);

	//function that accepts a string of borders as a parameters, goes through it, and adds the borders in the list
	bool addBorders(string input, map<int, Country*>* country );

};

//trims any whitespace from both sides of the string 
static inline string trim(string input);

