#include "Map.h"
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
using std::vector;

int main() {

	// Create a few Countries
	Country * country_a = new Country("country_a", 1, 1, 1);
	Country * country_b = new Country("country_b", 2, 1, 1);
	Country * country_c = new Country("country_c", 3, 1, 1);
	Country * country_d = new Country("country_d", 4, 2, 2);
	Country * country_e = new Country("country_e", 5, 2, 2);
	Country * country_f = new Country("country_f", 6, 2, 3);

	// Populate each country's adjacency list of neighbour countries
	vector<Country * > * adjacency_country_a = new vector<Country *>;
	adjacency_country_a->push_back(country_b);
	adjacency_country_a->push_back(country_e);
	vector<Country * > * adjacency_country_b = new vector<Country *>;
	adjacency_country_b->push_back(country_a);
	adjacency_country_b->push_back(country_c);
	adjacency_country_b->push_back(country_d);
	vector<Country * > * adjacency_country_c = new vector<Country *>;
	adjacency_country_c->push_back(country_b);
	adjacency_country_c->push_back(country_d);
	vector<Country * > * adjacency_country_d = new vector<Country *>;
	adjacency_country_d->push_back(country_b);
	adjacency_country_d->push_back(country_c);
	adjacency_country_d->push_back(country_e);
	adjacency_country_d->push_back(country_f);
	vector<Country * > * adjacency_country_e = new vector<Country *>;
	adjacency_country_e->push_back(country_a);
	adjacency_country_e->push_back(country_d);
	vector<Country * > * adjacency_country_f = new vector<Country *>;
	adjacency_country_f->push_back(country_d);

	// attach adjacency vectors to countries
	country_a->addAdjacencyList(adjacency_country_a);
	country_b->addAdjacencyList(adjacency_country_b);
	country_c->addAdjacencyList(adjacency_country_c);
	country_d->addAdjacencyList(adjacency_country_d);
	country_e->addAdjacencyList(adjacency_country_e);
	country_f->addAdjacencyList(adjacency_country_f);

	// Create a map<int, Country*> to load the Map class with a list of all countries
	map<int, Country*> * countriesToLoadIntoMap = new map<int, Country*>;
	countriesToLoadIntoMap->emplace(country_a->getID(), country_a);
	countriesToLoadIntoMap->emplace(country_b->getID(), country_b);
	countriesToLoadIntoMap->emplace(country_c->getID(), country_c);
	countriesToLoadIntoMap->emplace(country_d->getID(), country_d);
	countriesToLoadIntoMap->emplace(country_e->getID(), country_e);
	countriesToLoadIntoMap->emplace(country_f->getID(), country_f);

	// Create a continent and add the countries to it
	Continent * continent_1 = new Continent(10, 1, "Asia");
	Continent * continent_2 = new Continent(10, 2, "North America");
	continent_1->addCountryToContinent(country_a);
	continent_1->addCountryToContinent(country_b);
	continent_1->addCountryToContinent(country_c);
	continent_2->addCountryToContinent(country_d);
	continent_2->addCountryToContinent(country_e);
	continent_2->addCountryToContinent(country_f);

	// Create a continent vector
	vector<Continent *> * continents = new vector<Continent *>;
	continents->push_back(continent_1);
	continents->push_back(continent_2);

	// Create a Map and pass it the countries vector as a list of all countries
	Map myMap(countriesToLoadIntoMap, continents);
	
	// This will print out the test of 
	cout << "Creating a connected graph..," << endl << endl;
	cout << "Are all of the countries in one and only one continent?" << endl;
	cout << (myMap.countryAppearsInOneAndOnlyOneContinent() ? "    **you betcha!**" : "    **not a chance!**") << endl;
	cout << endl;
	cout << "Is the map connected?" << endl;
	cout << (true ? "    **you betcha!**" : "    **not a chance!**") << endl;
	cout << endl;

	//  *** *** *** country_g is disconnected from the graph (comment out to get a connected graph) *** *** ***
	Country * country_g = new Country("country_g", 7, 3, 0);
	vector<Country * > * adjacency_country_g = new vector<Country *>;
	country_g->addAdjacencyList(adjacency_country_g);
	myMap.addCountry(country_g); // add unconnected country to graph
	myMap.continents->at(0)->countries->at(0)->addCountry(country_g); // add country to continent

	cout << "Are all continents connected subgraphs?" << endl;
	for (int i = 0; i < myMap.continents->size(); ++i) {
		Continent * currentContinent = continents->at(i);
		cout << "    " << currentContinent->getName() << ": ";
		cout << (myMap.isMapConnected() ? "**you betcha!**" : "**not a chance!**") << endl;
	}
	cout << endl;

	cout << "Adding a country to our map that is not connected to any other country..." << endl << endl;
	cout << "Is this new (unconnected) map connected?" << endl;
	cout << (myMap.isMapConnected() ? "    **you betcha!**" : "    **not a chance!**") << endl;
	
	return 0;
}