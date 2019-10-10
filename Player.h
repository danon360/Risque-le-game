#pragma once
#include "Dice.h"
#include "Map.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class Player {
    
public:
    // Vector that has a collection of countries
    vector<Country*> * countriesOwned;
    
    
    
    
    // Player Constructor
    Player();
    void addCountries(Country * newCountry);
    void collectionOfCountries();
    void collectionOfRiskCards();
    void diceObject();
    void reinforce();
    void attack();
    void fortify();
    
private:
    Dice myDice;
    
    

    
   
    
};
