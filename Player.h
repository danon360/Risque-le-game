#pragma once
#include <string>
#include "Map.h"
#include "Dice.h"
#include "Cards.h"
//#include "Cards.h"


class Player  {
    
public:
    // Player Constructor and Destructor
    Player();
    ~Player();
    
    // DICE METHODS
    void diceObject();
    
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
        name = newName;
        
    }
    
    // Game methods
    void reinforce(Player* player);
    void attack(Player* player);
    void fortify();


	vector<Country*>* getCountriesOwned();

	Country selectCountry(std::vector<Country> countries);

    int selectArmiesToReinforce( Country& country, int armiesRemaining);


private:
     // Vector that has countriesOwned
     vector<Country*> * countriesOwned;
    
     // Dice Object
     Dice myDice;

    // Hand object for each player
	 Hand* playerHand;

    
    string* name;
    
    // vector<Card*> * cardsOwned;
    
};
