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
	int * ID;
	int * troopCount;
	vector<Country*> * adjacentCountries;

public:
	Country(string nm, int id);
	~Country();
	string* toString(); // prints the default output for a country object
	bool equals(Country * otherCountry); // 2 countries are equal if they have the same name (assuming no name duplicates at MapLoader stage)
	void setName(string newName);
	string getName();
	void setID(int newID);
	int getID();
	void setTroopCount(int newTroopCount);
	void addToTroopCount(int toAdd);
	void setTroopCount(int newCount);
	int getTroopCount();

	void addAdjacencyList(vector<Country* > * adjacentCountriesList);
	vector<Country*> * getAdjacencyList();
	void addAdjacentCountry(Country * toAdd);
};

class Map {

public:
	Map(vector<Country*> * countryList);
	~Map();
	void addCountriesToMap(vector<Country*> * newContinent); // adds countries to the vector and increments the number of continents
	void addContinent(vector<Country*> * newContinent); // adds a continent to the vector and increments the number of continents


private:
	// Country attributes of map
	vector<Country*> * countriesInMap;

	// Continent attributes of map
	int * numContinents;
	vector<Continent*> * continentList;
	

	// Utility methods
	Country* findCountry(string name);
	bool validateMap();
	bool isCountryListConnected();
	bool continentCheck();
	
};


class Continent {

public:
	Continent(int countryCount, vector<Country*> * countryList);

private:
	int *numCountries;
	vector<Country*> * allCountries;
};