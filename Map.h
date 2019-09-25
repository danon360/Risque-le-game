#pragma once

#include "MapLoader.h"

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

class country {

private:
	string * name;
	int * continent;
	int * ID;

public:
	country();
	country(int id, string nm, int cont);

	string toString();
	
	int getId();

	int getCont();

	void addBorder(int border);

	string getName();
};