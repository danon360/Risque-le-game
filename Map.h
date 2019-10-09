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
	vector<Country*> * neighbours;

public:

	// Constructor / Destructor
	Country(string nm, int id);
	~Country();
	

	// General utilities
	string* toString(); // prints the default output for a country object
	bool equals(Country * otherCountry); // 2 countries are equal if they have the same name (assuming no name duplicates at MapLoader stage)

	// Setters/ Getters
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
	void addCountry(Country * toAdd);
};

class Map {

public:
	Map(vector<Country*> * countryList);
	~Map();
	void addCountry(Country* newCountry); // adds countries to the vector and increments the number of continents
	void addContinent(Continent * newContinent); // adds a continent to the vector and increments the number of continents
	bool validateMap();

private:
	// Country attributes of map
	vector<Country*> * countries;

	// Continent attributes of map
	vector<Continent*> * continents;
	
<<<<<<< HEAD
	int *size;
	vector<Country*> * allCountries;
	vector<Map> * continents[];

	Map(int newSize, vector<Country*> countryList);
	bool validateMap();
	bool isConnected();
	Country* findCountry(string name);
};
=======

	// Utility methods
	Country* findCountry(string name);
	Country* findCountry(Country * countryToFind);
	bool isMapConnected();
	bool continentCheck();
	
};


class Continent {

public:
	Continent();
	Continent(vector<Country*> * countryList);
	~Continent();
	void addCountry(Country * newCountry);
	Country* findCountry(string name);
	Country* findCountry(Country * countryToFind);
private:
	vector<Country*> * countries; // the countries that are in this continent
};
>>>>>>> bff5561615b23438bc7b6f2d99fee014de9789e0
