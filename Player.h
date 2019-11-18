
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
	void printSourceCountries(vector<struct attackPossibilities*>* attackTree);
	void printDestinationCountries(vector<struct attackPossibilities*>* attackTree, int sourceIndex);

	// Reinforce methods -----------------------------------
	virtual int doExchangeOfCards(Player* player) = 0;
	virtual void whereToAssignReinforceArmies(Player* player, int totalArmies) = 0;

	// Attack methods --------------------------------------
	virtual bool attackDecision(Player* player) = 0;
	virtual Country* chooseSourceCountryToAttackFrom(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int* sourceIndex) = 0;
	virtual Country* chooseDestinationCountryToAttack(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int sourceIndex) = 0;
	virtual int attackerChooseDice(Player* attacker, Player* defender, Country* source, Country* destination) = 0;
	virtual int defenderChooseDice(Player* attacker, Player* defender, Country* source, Country* destination) = 0;
	virtual bool continueAttacking(Player* player) = 0;
	virtual bool keepFightingAtCountry(Player* attacker, Player* defender, Country* source, Country* destination) = 0;
	virtual int howManyTroopsToTranferAfterAWin(Player* player, Country* conquered, Country* winner) = 0;

	// Fortify methods -------------------------------------
	virtual bool fortifyDecision(Player* player) = 0;
	virtual Country* whereToFortifyFrom(Player* player) = 0;
	virtual Country* whereToFortifyTo(Player* player, Country* countryFrom) = 0;
	virtual int howManyArmiesToFortifyWith(Player* player, Country* countryFrom, Country* countryTo) = 0;

};


class HumanStrategy : public PlayerStrategies {

public:

	// Constructors / Destructors --------------------------
	HumanStrategy();
	~HumanStrategy();

	// Setup methods ---------------------------------------

	// Reinforce methods -----------------------------------
	int doExchangeOfCards(Player* player);
	void whereToAssignReinforceArmies(Player* player, int totalArmies);
	
	// Attack methods --------------------------------------
	bool attackDecision(Player* player);
	Country* chooseSourceCountryToAttackFrom(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int* sourceIndex);
	Country* chooseDestinationCountryToAttack(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int sourceIndex);
	int attackerChooseDice(Player* attacker, Player* defender, Country* source, Country* destination);
	int defenderChooseDice(Player* attacker, Player* defender, Country* source, Country* destination);
	bool continueAttacking(Player* player);
	bool keepFightingAtCountry(Player* attacker, Player* defender, Country* source, Country* destination);
	int howManyTroopsToTranferAfterAWin(Player* player, Country* conquered, Country* winner);

	// Fortify methods -------------------------------------
	bool fortifyDecision(Player* player);
	Country* whereToFortifyFrom(Player* player);
	Country* whereToFortifyTo(Player* player, Country* countryFrom);
	int howManyArmiesToFortifyWith(Player* player, Country* countryFrom, Country* countryTo);

};


class AgressiveStrategy : public PlayerStrategies {

public:

	// Constructors / Destructors --------------------------
	AgressiveStrategy();
	~AgressiveStrategy();

	// Setup methods ---------------------------------------

	// Reinforce methods -----------------------------------
	int doExchangeOfCards(Player* player);
	void whereToAssignReinforceArmies(Player* player, int totalArmies) {};

	// Attack methods --------------------------------------
	bool attackDecision(Player* player);
	Country* chooseSourceCountryToAttackFrom(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int* sourceIndex);
	Country* chooseDestinationCountryToAttack(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int sourceIndex);
	int attackerChooseDice(Player* attacker, Player* defender, Country* source, Country* destination);
	int defenderChooseDice(Player* attacker, Player* defender, Country* source, Country* destination);
	bool continueAttacking(Player* player);
	bool keepFightingAtCountry(Player* attacker, Player* defender, Country* source, Country* destination);
	int howManyTroopsToTranferAfterAWin(Player* player, Country* conquered, Country* winner);

	// Fortify methods -------------------------------------
	bool fortifyDecision(Player* player);
	Country* whereToFortifyFrom(Player* player);
	Country* whereToFortifyTo(Player* player, Country* countryFrom);
	int howManyArmiesToFortifyWith(Player* player, Country* countryFrom, Country* countryTo);

private:

	Country * findMinTroopCountry(vector<Country*>* validMoveCountries);
	Country* findMaxTroopCountry(vector<Country*>* validMoveCountries);

};


class BenevolentStrategy : public PlayerStrategies {

public:

	// Constructors / Destructors --------------------------
	BenevolentStrategy();
	~BenevolentStrategy();

	// Setup methods ---------------------------------------

	// Reinforce methods -----------------------------------
	int doExchangeOfCards(Player* player);
	void whereToAssignReinforceArmies(Player* player, int totalArmies) {};

	// Attack methods --------------------------------------
	bool attackDecision(Player* player);
	Country* chooseSourceCountryToAttackFrom(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int* sourceIndex) { return nullptr; };
	Country* chooseDestinationCountryToAttack(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int sourceIndex) { return nullptr; };
	int attackerChooseDice(Player* attacker, Player* defender, Country* source, Country* destination);
	int defenderChooseDice(Player* attacker, Player* defender, Country* source, Country* destination);
	bool continueAttacking(Player* player);
	bool keepFightingAtCountry(Player* attacker, Player* defender, Country* source, Country* destination);
	int howManyTroopsToTranferAfterAWin(Player* player, Country* conquered, Country* winner);

	// Fortify methods -------------------------------------
	bool fortifyDecision(Player* player);
	Country* whereToFortifyFrom(Player* player);
	Country* whereToFortifyTo(Player* player, Country* countryFrom);
	int howManyArmiesToFortifyWith(Player* player, Country* countryFrom, Country* countryTo);

private:

	Country* findMinTroopCountry(vector<Country*>* validMoveCountries);
	Country* findMaxTroopCountry(vector<Country*>* validMoveCountries);

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
	void diceFacility(int* maxRoll, int* numOfArmies, int numDiceToRoll);

	// Attack helper methods
	void generateAttackTree(Player* player, vector<struct attackPossibilities*>* attackTree);
	void deleteAttackTree(vector<struct attackPossibilities*>* attackTree);
	void printSourceCountries(vector<struct attackPossibilities*>* attackTree);
	void printDestinationCountries(vector<struct attackPossibilities*>* attackTree, int sourceIndex);
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

