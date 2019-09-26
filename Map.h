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

class country {

private:
	string * name;
	int * continent;
	int * ID;
	vector<country> adjacentCountries;

public:
	country();
	country(int id, string nm, int cont);
	string toString();
	int getId();
	int getCont();
	void addBorder(country c);
	string getName();

	void addAdjacentCountry(country * toAdd);
};

class Map {

public:
	
	int *size;
	vector<country> * allCountries;
	vector<Map> * continents[];

	Map(int newSize, vector<country> countryList);
	bool validateMap();
	bool isConnected();
	country* findCountry(string name);
};