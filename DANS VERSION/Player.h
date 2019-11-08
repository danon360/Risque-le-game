
// local
#pragma once
#include <string>
#include "Map.h"
#include "Dice.h"
#include "Cards.h"
#include <iostream>


class Player  {

private:
	// Vector that has countriesOwned
	vector<Country*>* countriesOwned;
	Country* myCountry;				   

	// Dice Object
	Dice* myDice;

	// Hand object for each player
	Hand* playerHand;
	string* name;
	int* ID;
	Map* gameMap;
	bool* hasConqueredThisTurn;

	// methods to support attack()
	void generateAttackTree(Player * player, vector<struct attackPossibilities*> * attackTree);
	void deleteAttackTree(vector<struct attackPossibilities*> * attackTree);
	void printSourceCountries(vector<struct attackPossibilities*> * attackTree);
	void printDestinationCountries(vector<struct attackPossibilities*> * attackTree, int sourceIndex);
	Country* chooseSourceCountry(Country * eventualSource, vector<struct attackPossibilities*> * attackTree, int* sourceIndex);
	Country* chooseDestinationCountry(Country * eventualDestination, vector<struct attackPossibilities*> * attackTree, int sourceIndex);
	void fight(Country * source, Country * destination);
	void changeOwner(Country* conquered);

public:
    // Player Constructor and Destructor
	Player();
	Player(string * _name, int id, Map* map);

    ~Player();
    
    // DICE METHODS
	void diceFacility(int* maxRoll, int* numOfArmies);
	
	void setID(int* id) {
		ID = id;
	}
	int* getID() {
		return ID;
	}

    
    // COUNTRY METHODS
    void addCountries(Country * newCountry);
    void collectionOfCountries();
    
    // CARDS METHODS
    void addCards(Card * newCard);
    void collectionOfRiskCards();
    
	vector<Country*>* getCountriesOwned();


    string getName() {
        return *name;
    }
    
    void setName(string *newName) {
        *name = *newName;
        
    }

	Hand* getHand();
    
    // Game methods
    void reinforce();
    void attack();
    void fortify();





	void setMap(Map* map);

	bool getHasConqueredThisTurn() {
		return *hasConqueredThisTurn;
	}

	void resetHasConqueredThisTurn() {
		*hasConqueredThisTurn = false;
	}

	Country* selectCountry(std::vector<Country*>* countries);

    int selectArmiesToReinforce( Country& country, int armiesRemaining);

	int continentBonus();

	bool equals(Player* other);
	
	void addAdjacentCountries(Country* country);
    
    bool isAdjacentCountry(Country* country);
    
    void setTroopCount(int troop, Country* myCountry);
    int getTroopCount(Country* country);
    
    void compareDiceObjects(Player* player, Country* attackingCountry, Country* defendingCountry);
    

    
};
