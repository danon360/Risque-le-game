#include "Map.h"

/************************************************************************
                            Country functions
 ***********************************************************************/

Country::Country(string nm, int id) {
	name = new string(nm);
	ID = new int(id);
	troopCount = new int(0);
	neighbours = new vector<Country*>();
}

Country::Country(string nm, int id, vector<Country*> * adjacentCountries) {
	name = new string(nm);
	ID = new int(id);
	troopCount = new int(0);
	neighbours = adjacentCountries;
}

Country::~Country() {
	delete name;
	delete ID;
	delete troopCount;
	if (neighbours != nullptr) {
		for (int i = 0; i < neighbours->size(); ++i)
		delete neighbours;
		neighbours = nullptr;
	}
}

string Country::toString() {
	string str = "Name: " + *name + ", ID: " + std::to_string(*ID) + ", Troops: " + std::to_string(*troopCount);
	return str;
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
void Country::setContinentNumber(int continentNum) {
	*continentNumber = continentNum;
}
int Country::getContinentNumber() {
	return *continentNumber;
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

bool Country::isCountryAdjacentToMe(Country * otherCountry) {
	for (int i = 0; i < neighbours->size(); ++i) {
		if (neighbours->at(i) == otherCountry)
			return true;
	}
	return false;
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

void Map::addContinent(Continent* newContinent) {
	continents->push_back(newContinent);
}

bool Map::isMapConnected() {

	// initialize visited array with each country of the map's list and set visited flag to 'false'
	vector<visited*> * visitedArray = createVisitedList();
	
	bool isGraphConnected = false;

	if (areAllVisited(visitedArray)) { // base case: if all Countries are visited, we return true
		return true;
	}
	else { // check each country in list to see if it can reach all other countries

		for (int i = 0; i < visitedArray->size(); ++i) {
			isGraphConnected *= recuriveMapCheckConnected(visitedArray->at(i)->country, visitedArray);
		}

		
	}

	// second to last thing is to delete the visited list:
	deleteVisitedList(visitedArray);
	delete visitedArray;

	return isGraphConnected;
}

bool Map::recuriveMapCheckConnected(Country * country, vector<visited*> * visitedArray) {
	
	// do this for each country in the adjacencyList of current country
	for (int i = 0; i < country->getAdjacencyList()->size(); ++i) {

		if (!isCountryVisited(country, visitedArray)) {
			setCountryAsVisited(country, visitedArray);
			recuriveMapCheckConnected(country->getAdjacencyList()->at(i + 1), visitedArray);
		}
	}

	// TODO: Delete this return and make this function correct
	return false;
}

bool Map::setCountryAsVisited(Country * country, vector<visited*> * visitedArray) {

	// Find our country in visitedArray and set its visited flag to 'true'
	for (int i = 0; i < visitedArray->size(); ++i) {
		if (country == visitedArray->at(i)->country)
			visitedArray->at(i)->isVisited = true;
	}
	// TODO: Delete this return and make this function correct
	return false;
}

bool Map::isCountryVisited(Country * country, vector<visited*> * visitedArray) {

	// look through visitedArray to see if our country has been visited or not
	for (int i = 0; i < visitedArray->size(); ++i) {
		if (country == visitedArray->at(i)->country) {
			if (visitedArray->at(i)->isVisited)
				return true;
			else
				return false;
		}
	}

	return false;
}

vector<Map::visited*> * Map::createVisitedList() {

	vector<Map::visited*> * visitedArray = new vector<Map::visited*>;

	for (int i = 0; i < countries->size(); ++i) {
		visited* v = new visited;
		v->isVisited = false;
		v->country = countries->at(i);
		visitedArray->push_back(v);
	}

	return visitedArray;
}

bool Map::areAllVisited(vector<visited*> * visitedArray) {
	bool areAllVisited = false;
	for (int i = 0; i < visitedArray->size(); ++i) {
		areAllVisited = visitedArray->at(i)->isVisited;
	}
	return areAllVisited;
}

void Map::deleteVisitedList(vector<visited*> * visitedArray) {
	for (int i = 0; i < visitedArray->size(); ++i) {
		delete visitedArray->at(i);
	}
}

/************************************************************************
                           Continent functions
 ***********************************************************************/

Continent::Continent(int bonusPoints) {
	*troopBonus = bonusPoints;
	countries = new vector<Country*>;
}

Continent::Continent(int bonusPoints, vector<Country*> * countryList) {
	*troopBonus = bonusPoints;
	countries = countryList;
}
Continent::~Continent() {
	delete troopBonus;
}

void Continent::setTroopBonus(int newBonus) {
	troopBonus = new int(newBonus);
}

int Continent::getTroopBonus() {
	return *troopBonus;
}

void Continent::addCountry(Country * newCountry) {
	countries->push_back(newCountry);
}

Country* Continent::findCountry(string name) {

}

Country* Continent::findCountry(Country * countryToFind) {

}




