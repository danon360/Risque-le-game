#include "Map.h"
#include "MapLoader.h"
#include "MapLoader.cpp"

#include <iostream>
#include <vector>
#include <string>;

using std::cout;
using std::endl;

# MAP CLASS FUNCTION IMPLEMENTATION---------------------------------------------------------------------- -

Map::Map(int newSize, vector<country> countryList) {
	*size = newSize;
	allCountries = &countryList;
}

bool Map::validateMap() {

	return false;
}

bool Map::isConnected() {

	return false;
}

country* Map::findCountry(string name) {

	for (int i = 0; i < allCountries->size(); ++i) {

		allCountries->at(i).getName();

	}


	return NULL;
}


# COUNTRY CLASS FUNCTION IMPLEMENTATION -----------------------------------------------------------------------

country::country() {
	name = &string(" ");
}

country::country(int id, string nm, int cont) {
	ID = &id;
	name = &nm;
	continent = &cont;
}

string country::toString() {
	return *name;
}

int country::getId() {
	return *ID;
}

int country::getCont() {
	return *continent;
}

void country::addBorder(int border) {
	cout << this->ID << " : added border " << border << endl;
}

string country::getName() {
	return *name;
}