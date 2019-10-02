#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Country {

private:
	string * name;
	int * continent;
	int * ID;
	vector<Country> adjacentCountries;

public:
	Country();
	Country(int id, string nm, int cont);
	string toString();
	int getId();
	int getCont();
	void addBorder(Country c);
	string getName();

	void addAdjacentCountry(Country * toAdd);
};

class Map {

public:
	
	int *size;
	vector<Country> * allCountries;
	vector<Map> * continents[];

	Map(int newSize, vector<Country> countryList);
	bool validateMap();
	bool isConnected();
	Country* findCountry(string name);
};