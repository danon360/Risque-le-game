
/*
	THIS IS GARBAGE CLASS, DO NOT MERGE! USE THE VERSION ON THE REPO!!!!
*/

#pragma once
#include <string>
#include "Map.h"
#include "Dice.h"
#include "Cards.h"
#include <iostream>
//#include "GameEngine.h"


class Player  {

private:
	// Vector that has countriesOwned
	vector<Country*>* countriesOwned;

	// Dice Object
	Dice* myDice;

	// Hand object for each player
	Hand* playerHand;
	string* name;
	int* ID;
	Map* gameMap;

	//GameEngine* mapGame;


public:
    // Player Constructor and Destructor
	Player();
	Player(string * _name, int id, Map* map);
	Player(vector<Country*>* playerCountries, Dice* playerDice, Hand* hand, string* playerName);

    ~Player();
    
    // DICE METHODS
    void diceObject();

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
    //void addCards(Card * newCard);
    //void collectionOfRiskCards();
    
    
    string getName() {
        return *name;
    }
    
    void setName(string *newName) {
        *name = *newName;
        
    }

	Hand* getHand();
    
    // Game methods
    void reinforce(Player* player);
    void attack(Player* player);
    void fortify(Player* player);


	vector<Country*>* getCountriesOwned();

	Country* selectCountry(std::vector<Country*>* countries);

    int selectArmiesToReinforce( Country& country, int armiesRemaining);

	int continentBonus();



    
};
