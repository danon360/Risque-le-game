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

void main() {

	// Create a few Countries
	Country * country_a = new Country("country_a", 1, 1);
	Country * country_b = new Country("country_b", 2, 1);
	Country * country_c = new Country("country_c", 3, 1);
	Country * country_d = new Country("country_d", 4, 2);
	Country * country_e = new Country("country_e", 5, 2);
	Country * country_f = new Country("country_f", 6, 2);

	country_a->setContinentNumber(1);
	country_b->setContinentNumber(1);
	country_c->setContinentNumber(1);
	country_d->setContinentNumber(2);
	country_e->setContinentNumber(2);
	country_f->setContinentNumber(2);

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

	// This is the main country list that will go into the Map
	vector<Country * > * countries = new vector<Country *>;
	countries->push_back(country_a);
	countries->push_back(country_b);
	countries->push_back(country_c);
	countries->push_back(country_d);
	countries->push_back(country_e);
	countries->push_back(country_f);

	// Create a Map and pass it the countries vector as a list of all countries
	Map myMap(countries);
	
	//  *** *** *** country_g is disconnected from the graph (comment out to get a connected graph) *** *** ***
	Country * country_g = new Country("country_g", 7, 3);
	vector<Country * > * adjacency_country_g = new vector<Country *>;
	country_g->addAdjacencyList(adjacency_country_g);
	//countries->push_back(country_g);
	
}