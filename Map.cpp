#include "Map.h"

Map::Map(int newSize, vector<Country> countryList) {
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
Country* Map::findCountry(string name) {

	for (int i = 0; i < allCountries->size(); ++i) {

		if (allCountries->at(i).getName().compare(name))
			return &(allCountries->at(i));
	}

	return NULL;
}

Country::Country() {
	name = new string("");
}

Country::Country(int id, string nm, int cont) {
	ID = new int(id);
	name = new string(nm);
	continent = new int(cont);
}

string Country::toString() {
	return *name;
}

int Country::getId() {
	return *ID;
}

int Country::getCont() {
	return *continent;
}

void Country::addBorder(Country c) {
	cout << this->ID << " : added border " << c.getName << endl;
}

string Country::getName() {
	return *name;
}

void Country::addAdjacentCountry(Country * toAdd) {
	if (toAdd != nullptr) {

	}
}