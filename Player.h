
// local
#pragma once
#include <string>
#include "Map.h"
#include "Dice.h"
#include "Cards.h"
#include <iostream>

// Forward declaration
class Player;

class PlayerStrategies
{

public:

	// Constructors / Destructors --------------------------
	PlayerStrategies();
	~PlayerStrategies();

	// Setup methods ---------------------------------------


	// Reinforce methods -----------------------------------
	virtual int doExchangeOfCards(Player* player) = 0;
	virtual void whereToAssignReiforceArmies(Player* player, int totalArmies) = 0;

	// Attack methods --------------------------------------
	virtual void attackDecision() = 0;

	// Fortify methods -------------------------------------
	virtual void fortifyDecision() = 0;
};

class HumanStrategy : public PlayerStrategies {

public:

	// Constructors / Destructors --------------------------
	HumanStrategy();
	~HumanStrategy();

	// Setup methods ---------------------------------------


	// Reinforce methods -----------------------------------
	int doExchangeOfCards(Player* player);
	void whereToAssignReiforceArmies(Player* player, int totalArmies);

	// Attack methods --------------------------------------


	// Fortify methods -------------------------------------


};

class AgressiveStrategy : public PlayerStrategies {

public:

	// Constructors / Destructors --------------------------
	AgressiveStrategy();
	~AgressiveStrategy();

	// Setup methods ---------------------------------------


	// Reinforce methods -----------------------------------


	// Attack methods --------------------------------------


	// Fortify methods -------------------------------------
};

class BenevolentStrategy : public PlayerStrategies {

public:

	// Constructors / Destructors --------------------------
	BenevolentStrategy();
	~BenevolentStrategy();

	// Setup methods ---------------------------------------


	// Reinforce methods -----------------------------------


	// Attack methods --------------------------------------


	// Fortify methods -------------------------------------
};


class Player {

private:

	// Vector that has countriesOwned
	vector<Country*>* countriesOwned;
	Country* myCountry;

	// Strategy pattern
	PlayerStrategies* strategy;

	// Dice Object
	Dice* myDice;

	// Hand object for each player
	Hand* playerHand;
	string* name;
	int* ID;
	Map* gameMap;
	bool* hasConqueredThisTurn;

	// DICE METHODS
	void diceFacility(int* maxRoll, int* numOfArmies);

	// Attack helper methods
	void generateAttackTree(Player* player, vector<struct attackPossibilities*>* attackTree);
	void deleteAttackTree(vector<struct attackPossibilities*>* attackTree);
	void printSourceCountries(vector<struct attackPossibilities*>* attackTree);
	void printDestinationCountries(vector<struct attackPossibilities*>* attackTree, int sourceIndex);
	Country* chooseSourceCountry(Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int* sourceIndex);
	Country* chooseDestinationCountry(Country* eventualDestination, vector<struct attackPossibilities*>* attackTree, int sourceIndex);
	void fight(Country* source, Country* destination);
	void changeOwner(Country* conquered, Country* winner);
	void compareDiceObjects(Player* player, Country* attackingCountry, Country* defendingCountry);

public:
	// Player Constructor and Destructor
	Player();
	Player(string* _name, int id, Map* map);
	~Player();

	// Game methods
	void reinforce();
	void attack();
	void fortify();

	// COUNTRY METHODS
	void addCountries(Country* newCountry);
	void addACountry(Country* toAdd);
	void collectionOfCountries();

	// Reiforce helper methods
	int selectArmiesToReinforce(Country& country, int armiesRemaining);
	int continentBonus();

	// Set/Get/Equals/toString
	vector<Country*>* getCountriesOwned();
	void setID(int* id) { ID = id; }
	int* getID() { return ID; }
	string getName() { return *name; }
	void setName(string* newName) { *name = *newName; }
	bool getHasConqueredThisTurn() { return *hasConqueredThisTurn; }
	void resetHasConqueredThisTurn() { *hasConqueredThisTurn = false; }
	Country* selectCountry(std::vector<Country*>* countries);
	void setTroopCount(int troop, Country* myCountry);
	int getTroopCount(Country* country);
	bool equals(Player* other);
	PlayerStrategies* getStrategy() { return strategy; }
	void setStrategy(PlayerStrategies* newStrategy) { strategy = newStrategy; }
	Hand* getHand();

};


