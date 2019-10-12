#include "Map.h"

/************************************************************************

                            Country functions

 ***********************************************************************/

Country::Country(string nm, int id, int continentNum, int ownerPlayer) {
	name = new string(nm);
	ID = new int(id);
	troopCount = new int(0);
	ownerID = new int(ownerPlayer);
	continentNumber = new int(continentNum);
	neighbours = new vector<Country*>();
}

Country::Country(string nm, int id, int continentNum, int ownerPlayer, vector<Country*> * adjacentCountries) {
	name = new string(nm);
	ID = new int(id);
	troopCount = new int(0);
	ownerID = new int(ownerPlayer);
	continentNumber = new int(continentNum);
	neighbours = adjacentCountries;
}

Country::~Country() {
	delete name;
	delete ID;
	delete troopCount;
	delete continentNumber;
	delete ownerID;
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
	// countries are equal if their ID's are equal
	return (this->getID() == otherCountry->getID());
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

				        UndirectedGraph functions

 ***********************************************************************/

UndirectedGraph::UndirectedGraph() {
	countries = new vector<Country*>;
	countryDictionary = nullptr;
}
UndirectedGraph::UndirectedGraph(map<int, Country*> * mapOfCountries) {
	countryDictionary = mapOfCountries;
	countries = new vector<Country*>;

	// populate the vector from the map
	for (std::map<int, Country*>::iterator it = countryDictionary->begin(); it != countryDictionary->end(); ++it) {
		countries->push_back(it->second);
	}

}
UndirectedGraph::UndirectedGraph(vector<Country*> * countryList) {
	countries = countryList;
	countryDictionary = nullptr;
}
UndirectedGraph::~UndirectedGraph() {
	// intentionally left blank
}

void UndirectedGraph::addCountry(Country* newCountry) {
	countries->push_back(newCountry);
}

bool UndirectedGraph::isMapConnected() {

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

	return isGraphConnected;
}
bool UndirectedGraph::recuriveMapCheckConnected(Country * country, vector<visited*> * visitedArray) {

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
bool UndirectedGraph::setCountryAsVisited(Country * country, vector<visited*> * visitedArray) {

	// Find our country in visitedArray and set its visited flag to 'true'
	for (int i = 0; i < visitedArray->size(); ++i) {
		if (country == visitedArray->at(i)->country)
			visitedArray->at(i)->isVisited = true;
	}
	// TODO: Delete this return and make this function correct
	return false;
}
bool UndirectedGraph::isCountryVisited(Country * country, vector<visited*> * visitedArray) {

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
vector<UndirectedGraph::visited*> * UndirectedGraph::createVisitedList() {

	vector<UndirectedGraph::visited*> * visitedArray = new vector<UndirectedGraph::visited*>;

	for (int i = 0; i < countries->size(); ++i) {
		visited* v = new visited;
		v->isVisited = false;
		v->country = countries->at(i);
		visitedArray->push_back(v);
	}

	return visitedArray;
}
bool UndirectedGraph::areAllVisited(vector<visited*> * visitedArray) {
	bool areAllVisited = false;
	for (int i = 0; i < visitedArray->size(); ++i) {
		areAllVisited = visitedArray->at(i)->isVisited;
	}
	return areAllVisited;
}

Country* UndirectedGraph::findCountry(int countryID){
	for (int i = 0; i < countries->size(); ++i) {
		if (countries->at(i)->getID() == countryID)
			return countries->at(i);
	}
	return nullptr;
}
Country* UndirectedGraph::findCountry(string name) {
	for (int i = 0; i < countries->size(); ++i) {
		if (countries->at(i)->getName().compare(name) == 0)
			return countries->at(i);
	}
	return nullptr;
}
Country* UndirectedGraph::findCountry(Country * countryToFind) {
	for (int i = 0; i < countries->size(); ++i) {
		if (countries->at(i) == countryToFind)
			return countries->at(i);
	}
	return nullptr;
}

/************************************************************************

							   Map functions

 ***********************************************************************/

Map::Map() {
	countryDictionary = nullptr;
	countries = new vector<Country*>;
	continents = new vector<Continent *>;
}
Map::Map(map<int, Country*> * mapOfCountries) {
	countryDictionary = mapOfCountries;
	countries = new vector<Country*>;
	continents = new vector<Continent *>;

	// populate the vector from the map
	for (std::map<int, Country*>::iterator it = countryDictionary->begin(); it != countryDictionary->end(); ++it) {
		countries->push_back(it->second);
	}

}

Map::Map(map<int, Country*> * mapOfCountries, vector<Continent*> * continentsList) {
	countryDictionary = mapOfCountries;
	continents = continentsList;
	countries = new vector<Country*>;

	// populate the vector from the map
	for (std::map<int, Country*>::iterator it = countryDictionary->begin(); it != countryDictionary->end(); ++it) {
		countries->push_back(it->second);
	}
}

Map::Map(vector<Country*> * countryList) {
	countryDictionary = nullptr;
	countries = countryList;
	continents = new vector<Continent *>;
}

Map::~Map() {
	// intentionally left empty: need to figure out deleting vectors properly @Daniel TS
}

Country* Map::findCountryInContinent(int countryID) {

	for (int i = 0; i < continents->size(); ++i) {

		Country * currentCountry = continents->at(i)->findCountry(countryID);

		if (currentCountry->getID() == countryID) {
			return currentCountry;
		}
	}
	return nullptr;
}
Country* Map::findCountryInContinent(string name) {

	for (int i = 0; i < continents->size(); ++i) {

		Country * currentCountry = continents->at(i)->findCountry(name);

		if (currentCountry->getName().compare(name) == 0) {
			return currentCountry;
		}
	}
	return nullptr;
}
Country* Map::findCountryInContinent(Country * countryToFind) {

	for (int i = 0; i < continents->size(); ++i) {

		Country * currentCountry = continents->at(i)->findCountry(countryToFind);

		if (currentCountry == countryToFind) {
			return currentCountry;
		}
	}
	return nullptr;
}

void Map::addContinent(Continent* newContinent) {
	continents->push_back(newContinent);
}

bool Map::countryAppearsInOnlyOneContinent() {

	for (int i = 0; i < countries->size(); ++i) { // for each country in map

		int foundSameCountryNTimesInContinent = 0;

		Country * currentCountry = countries->at(i);

		for (int j = 0; j < continents->size(); ++j) { // for each continent in the map

			Continent * currentContinent = continents->at(j);

			for (int k = 0; k < currentContinent->countries->size(); ++k) { // for each country in continent

				Country * currentContinentCounty = currentContinent->countries->at(k);

				if (currentCountry->equals(currentContinentCounty))
					++foundSameCountryNTimesInContinent;

				if (foundSameCountryNTimesInContinent > 1)
					return false;
			}
		}
	}

	return true;
}

/************************************************************************

                           Continent functions

 ***********************************************************************/

Continent::Continent(int bonusPoints, int newID, string newName) {
	troopBonus = new int(bonusPoints);
	ID = new int(newID);
	name = new string(newName);
	countries = new vector<Country*>;
}

Continent::Continent(int bonusPoints, int newID, string newName, vector<Country*> * countryList) {
	troopBonus = new int(bonusPoints);
	ID = new int(newID);
	name = new string(newName);
	countries = countryList;
}
Continent::~Continent() {
	delete troopBonus;
	delete ID;
	delete name;
}

void Continent::setTroopBonus(int newBonus) {
	*troopBonus = newBonus;
}
int Continent::getTroopBonus() {
	return *troopBonus;
}
void Continent::setID(int newID) {
	*ID = newID;
}
int Continent::getID() {
	return *ID;
}
void Continent::setName(string newName) {
	*name = newName;
}
string Continent::getName() {
	return *name;
}

void Continent::addCountryToContinent(Country * countryToAdd) {
	countryToAdd->setContinentNumber(*ID); // set the continent id of the country you just added to a continent
	countries->push_back(countryToAdd);
}







