#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

/************************************************************************

							  Country Class

 ***********************************************************************/

class Country {

private:

	string * name;
	int * continentNumber;
	int * ID;
	int * troopCount;
	int * ownerID;
	vector<Country*> * neighbours;

public:

	// Constructor / Destructor
	Country(string nm, int id, int continentNum, int ownerPlayer);
	Country(string nm, int id, int continentNum, int ownerPlayer, vector<Country*> * adjacentCountries);  // with a prefilled vector
	Country();
	~Country();
	
	// General utilities
	string toString(); // prints the default output for a country object
	bool equals(Country * otherCountry); // 2 countries are equal if they have the same name (assuming no name duplicates at MapLoader stage)

	// Setters/ Getters
	void setName(string newName);
	string getName();
	void setContinentNumber(int continentNum);
	int getContinentNumber();
	void setID(int newID);
	int getID();
	void setTroopCount(int newTroopCount);
	void addToTroopCount(int toAdd);
	int getTroopCount();
	void addAdjacencyList(vector<Country* > * adjacentCountriesList);
	vector<Country*> * getAdjacencyList(); // returns the list of neighbours
	void addCountry(Country * toAdd); // adds a country to the list of neighbours
	int getOwnerID();
	void setOwnerID(int id);

	// Utility functions
	bool isCountryAdjacentToMe(Country * otherCountry); // 'true' if otherCountry is in this->neighbours

};

/************************************************************************

	                      UndirectedGraph Class

 ***********************************************************************/

class UndirectedGraph {

public:

	// Country attributes of map holds all countries in this map
	vector<Country*> * countries;
	map<int, Country*> *  countryDictionary; // <country ID, Country *>

	// This struct (visited list) is used by graph methods for different traversals
	struct visited {
		bool isVisited = false;
		Country * country = nullptr;
	};

	// Utility methods
	bool areAllVisited(vector<visited*> * visitedArray); // checks the visitedArray to see if all nodes were visited
	vector<UndirectedGraph::visited*> * createVisitedList();
	bool isCountryVisited(Country * country, vector<visited*> * visitedArray);
	bool recuriveMapCheckConnected(Country * country, vector<visited*> * visitedArray);
	bool setCountryAsVisited(Country * country, vector<visited*> * visitedArray);
	UndirectedGraph();
	UndirectedGraph(map<int, Country*> *);
	UndirectedGraph(vector<Country*> * countryList);
	~UndirectedGraph();
	void addCountry(Country* newCountry); // adds countries to the vector and increments the number of continents
	bool isMapConnected();
	Country* findCountry(int countryID);
	Country* findCountry(string name);
	Country* findCountry(Country * countryToFind);
	virtual bool subclassSpecificMapConnectionCheck(Country * aCountry); // check used by isMapConnecte() => specific to each subclass 
	vector<Country*> * neighbourListForRecursive(Country * aCountry);
	void printGraph();
};

/************************************************************************

							Continent Class

 ***********************************************************************/

class Continent : public UndirectedGraph {

private:

	int * troopBonus;
	int * ID;
	string * name;

public:

	// Constructor / Destructor
	Continent(int bonusPoints, int newID, string newName);
	Continent(int bonusPoints, int newID, string newName, vector<Country*> * countryList);
	~Continent();

	// Setters/ Getters
	void setTroopBonus(int newBonus);
	int getTroopBonus();
	void setID(int newID);
	int getID();
	void setName(string newName);
	string getName();
	void addCountryToContinent(Country * countryToAdd);
	bool subclassSpecificMapConnectionCheck(Country * aCountry); // specific check for isMapConnected() ensure continent is equal
	// vector<Country*> * neighbourListForRecursive(Country * aCountry);
};

/************************************************************************

							   Map Class

 ***********************************************************************/

class Map : public UndirectedGraph {

public:

	// Continent attributes of map holds all continents (continents are a list of countries)
	vector<Continent*> * continents;

	// This struct (visited list) is used by graph methods for different traversals
	struct visited {
		bool isVisited = false;
		Country * country = nullptr;
	};

	Map();
	Map(map<int, Country*> *);
	Map(map<int, Country*> *, vector<Continent*> * continentsList);
	Map(vector<Country*> * countryList);
	~Map();

	Country* findCountryInContinent(int countryID);
	Country* findCountryInContinent(string name);
	Country* findCountryInContinent(Country * countryToFind);

	void addContinent(Continent * newContinent); // adds a continent to the vector and increments the number of continents
	bool countryAppearsInOneAndOnlyOneContinent(); // ensures that a country belongs to only one continent
	bool subclassSpecificMapConnectionCheck(Country * aCountry);
	// vector<Country*> * neighbourListForRecursive(Country * aCountry);
};


