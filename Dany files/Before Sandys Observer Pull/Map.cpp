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

// constructor for testing purposes
Country::Country() {
	name = new string("blank");
	continentNumber = new int(0);
	ID = new int(0);
	troopCount = new int(0);
	ownerID = new int(0);
	neighbours = new vector<Country*>;
}

Country::~Country() {
	delete name;
	delete ID;
	delete troopCount;
	delete continentNumber;
	delete ownerID;
	if (neighbours != nullptr) {
		for (int i = 0; i < neighbours->size(); ++i)
			delete neighbours->at(i);
		delete neighbours;
		neighbours->clear();
		neighbours = nullptr;
	}
	// note: do not need to delete the owner as it is a country that was deleted just above
}


int Country::getOwnerID() {
	return *ownerID;
}

void Country::setOwnerID(int id) {
	ownerID = new int(id);
}


string Country::toString() {
	string str = "Name: " + *name + ", ownerID: " + std::to_string(*ownerID) + ", Troops: " + std::to_string(*troopCount);
	return str;
}
bool Country::equals(Country* otherCountry) {
	// countries are equal if their ID's are equal
	return (getID() == otherCountry->getID());
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

bool UndirectedGraph::subclassSpecificMapConnectionCheck(Country * aCountry) {
	return true;
}

// ------------ isMapConnected() method and helpers ---------------------------------------------

bool UndirectedGraph::isMapConnected() {

	if (countries->size() == 0)
		return true;

	// holds the Countries and a flag of whether it was visited or not
	vector<UndirectedGraph::visited*> * visitedList = UndirectedGraph::createVisitedList();

	Country * currentCountry = countries->at(0);
	vector<Country*> * neighbourList = neighbourListForRecursive(currentCountry);

	return recuriveMapCheckConnected(currentCountry, visitedList);
}

bool UndirectedGraph::recuriveMapCheckConnected(Country * country, vector<visited*> * visitedArray) {

	setCountryAsVisited(country, visitedArray);

	if (areAllVisited(visitedArray)) { // positive base case
		return true;
	}
	else {

		vector<Country *> * neighbourList = country->getAdjacencyList();

		for (int i = 0; i < neighbourList->size(); ++i) {

			Country * currentNeighbour = neighbourList->at(i);

			if (!isCountryVisited(currentNeighbour, visitedArray) /*&&
				subclassSpecificMapConnectionCheck(country)*/) 
			{
				recuriveMapCheckConnected(currentNeighbour, visitedArray);
			}
		}

		if (areAllVisited(visitedArray)) // positive base case
			return true;

		// you get to then end of a row
		return false;
	}

	// TODO: Delete this return and make this function correct
	return false;
}
bool UndirectedGraph::setCountryAsVisited(Country * country, vector<visited*> * visitedArray) {

	// Find our country in visitedArray and set its visited flag to 'true'
	for (int i = 0; i < visitedArray->size(); ++i) {
		if (country->equals(visitedArray->at(i)->country)) {
			visitedArray->at(i)->isVisited = true;
			break;
		}
	}
	// TODO: Delete this return and make this function correct
	return false;
}
bool UndirectedGraph::isCountryVisited(Country * country, vector<visited*> * visitedArray) {

	// look through visitedArray to see if our country has been visited or not
	for (int i = 0; i < visitedArray->size(); ++i) {
		if (country->equals(visitedArray->at(i)->country)) { // find country in visited array
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

	for (int i = 0; i < visitedArray->size(); ++i) {
		if (!visitedArray->at(i)->isVisited) // if at least 1 Country is not visited then return false
			return false;
	}

	return true; // if you got through the loop then all countries must have been visited.
}

void UndirectedGraph::printGraph() {

	// print countries and their connections
	for (int i = 0; i < countries->size(); ++i) {

		Country * currentCountry = countries->at(i);
		vector<Country *> * currentCountryAdjacency = currentCountry->getAdjacencyList();

		std::cout << currentCountry->getName() << ": ";

		if (currentCountryAdjacency->size() == 0)
			std::cout << "NO NEIGHBOURS" << std::endl;
		else {
			for (int j = 0; j < currentCountryAdjacency->size(); ++j)
				std::cout << currentCountryAdjacency->at(j)->getName() << " ";
			std::cout << std::endl;
		}
	}
}

// ------------ END OF: isMapConnected() method and helpers ---------------------------------------

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

vector<Country*> * UndirectedGraph::neighbourListForRecursive(Country * aCountry) {
	return aCountry->getAdjacencyList();
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

	// set continentID in each country of the continents
	for (int i = 0; i < continents->size(); ++i) {

		Continent * currentContinent = continents->at(i);

		for (int j = 0; j < currentContinent->countries->size(); ++j) {

			Country * currentCountry = currentContinent->countries->at(j);
			currentCountry->setContinentNumber(currentContinent->getID());
		}
	}

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

bool Map::countryAppearsInOneAndOnlyOneContinent() {

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

		if (foundSameCountryNTimesInContinent != 1) // country is not in at least one continent
			return false;
	}

	return true;
}

bool Map::subclassSpecificMapConnectionCheck(Country * aCountry) {
	return true;
}

//vector<Country*> * Map::neighbourListForRecursive(Country * aCountry) {
//	return aCountry->getAdjacencyList();
//}

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

bool Continent::subclassSpecificMapConnectionCheck(Country * aCountry) {
	if (aCountry->getID() == getID())
		return true;

	return false;
}

//vector<Country*> * Continent::neighbourListForRecursive(Country * aCountry) {
//
//	vector<Country*> * neighbourList = new vector<Country*>;
//
//	for (int i = 0; i < aCountry->getAdjacencyList()->size(); ++i) {
//
//		if (aCountry->getContinentNumber() == this->getID()) {
//			neighbourList->push_back(aCountry->getAdjacencyList()->at(i));
//		}
//
//	}
//
//	return neighbourList;
//}
