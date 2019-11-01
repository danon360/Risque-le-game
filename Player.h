#pragma once
#include <string>
#include "Map.h"
#include "Dice.h"
//#include "Cards.h"


class Player {
    
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
    
    // name
    string getName() {
        return *name;
    }
    
    void setName(string *newName) {
        *name = *newName;
        
    }
    
    // Game methods
    void reinforce();
    void attack();
    void fortify();
    
private:
     // Vector that has countriesOwned
     vector<Country*> * countriesOwned;
    
     // Dice Object
     Dice myDice;
    
    string* name;
    
    // vector<Card*> * cardsOwned;
    
};
