#include "Map.h"

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

/* Given a String name, this will return a pointer to the country that has this name.
 */
country* Map::findCountry(string name) {

	for (int i = 0; i < allCountries->size(); ++i) {

		if (allCountries->at(i).getName().compare(name))
			return &(allCountries->at(i));
	}

	return NULL;
}

country::country() {
	name = new string("");
}

country::country(int id, string nm, int cont) {
	ID = new int(id);
	name = new string(nm);
	continent = new int(cont);
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

void country::addBorder(country c) {
	cout << this->ID << " : added border " << c.getName << endl;
}

string country::getName() {
	return *name;
}

void country::addAdjacentCountry(country * toAdd) {
	if (toAdd != nullptr) {

	}
}