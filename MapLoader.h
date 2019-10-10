#pragma once
#include"Map.h";
#include <map>;

using std::map;
using std::stringstream;
using std::ifstream;


//a temporary classes
class continent;

class MapLoader {
public:
	string* fileLocation;
	MapLoader();
	MapLoader(string location);
	void init();
	//function that takes a string containing the file location, and then procedes to load the file content into 3 seperate string pointers provided to it in the parameters
	void loadFileToStrings(string* fileLocation, string* continent, string* country, string* borders);

	//function that when given a string loads the continents into a vector and returns it
	vector<continent>* continentLoader(string input);

	//function that when given a string loads the countries into a vector and return it
	map<int, Country>* countryLoader(string input);

	//function that accepts a string of borders as a parameters, goes through it, and adds the borders in the list
	bool addBorders(string input, map<int, Country> country );

};

//trims any whitespace from both sides of the string 
static inline string trim(string input);

