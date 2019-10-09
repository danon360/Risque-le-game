#include "Map.h"

/************************************************************************
                            Country functions
 ***********************************************************************/

Country::Country(string nm, int id) {
	name = new string(nm);
	ID = new int(id);
	troopCount = new int(0);
}

Country::~Country() {
	delete name;
	delete ID;
	delete troopCount;
}

string* Country::toString() {
	string str = "Name: " + *name + ", ID: " + std::to_string(*ID) + ", Troops: " + std::to_string(*troopCount);
	return &str;
}
bool Country::equals(Country* otherCountry) {
	if ((*name).compare(otherCountry->getName()) == 0)
		return true;
}
void Country::setName(string newName) {
	*name = newName;
}
string Country::getName() {
	return *name;
}
void Country::setID(int newID) {
	*ID = newID;
}
int Country::getID() {
	return *ID;
}
void Country::setTroopCount(int newTroopCount) {
	*troopCount = newTroopCount;
}
void Country::addToTroopCount(int toAdd) {
	*troopCount += toAdd;
}
void Country::setTroopCount(int newCount) {
	*troopCount = newCount;
}
int Country::getTroopCount() {
	return *troopCount;
}

void Country::addAdjacencyList(vector<Country* > * adjacentCountriesList) {
	neighbours = adjacentCountriesList;
}

vector<Country*> * Country::getAdjacencyList() {
	return neighbours;
}

void Country::addCountry(Country * toAdd) {
	neighbours->push_back(toAdd);
}

/************************************************************************
							   Map functions
 ***********************************************************************/

Map::Map(vector<Country*> * countryList) {
	countries = countryList;
}

Map::~Map() {
	// intentionally left empty
}

void Map::addCountry(Country* newCountry) {
	countries->push_back(newCountry);
}

void Map::addContinent(Continent * newContinent) {
	continents->push_back(newContinent);
}


/************************************************************************
                           Continent functions
 ***********************************************************************/

Continent::Continent() {
	// intentionally left empty
}

Continent::Continent(vector<Country*> * countryList) {
	countries = countryList;
}
Continent::~Continent() {
	// intentionally left empty
}

void Continent::addCountry(Country * newCountry) {
	countries->push_back(newCountry);
}


