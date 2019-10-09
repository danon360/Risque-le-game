#include "Player.h"
#include "Map.h"
#include "Dice.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Player::Player() {
    myDice.rollDice(3);

    
}

void Player::addCountries(Country * newCountry) {
    countriesOwned->push_back(newCountry);

    
}

void Player::collectionOfCountries() {
    for(int i = 0; i < countriesOwned->size(); i++) {
        cout << countriesOwned->at(i)->getName()<< endl;
    }
    
}


// Reinforce method
void Player::reinforce() {
    cout << "Reinforced" << endl;
}

// Attack method
void Player::attack() {
    cout << "Attacked!!!" << endl;
}

// Fortify method
void Player::fortify() {
    cout << "fortified" << endl;
}



int main() {
    vector<Country*> countryList;
    countryList.push_back(new Country(1, "c1", 2));
    countryList.push_back(new Country(1, "c1", 2));
    countryList.push_back(new Country(1, "c1", 2));
    countryList.push_back(new Country(1, "c1", 2));
    countryList.push_back(new Country(1, "c1", 2));
    
    Map m1(5, countryList);
    
    
    
    
    
    
    Player p1;
    
    p1.addCountries(countryList.at(0));
    p1.collectionOfCountries();
    
    
}







