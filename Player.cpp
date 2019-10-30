#include "Player.h"
#include "Map.h"
#include <iostream>
using namespace std;
using std::vector;

// Default Constructor
Player::Player() {
    countriesOwned = new vector<Country*>;
    //cardsOwned = new vector<Card*>;
}

// Destructor
Player::~Player() {
    
    delete countriesOwned;
    countriesOwned = NULL;
    
    
   // delete cardsOwned;
   // cardsOwned = NULL;
    
}

// COUNTRY METHODS
// Method that adds countries
void Player::addCountries(Country *country) {
    countriesOwned->push_back(country);
}

// Displays the countries owned by this player
void Player::collectionOfCountries() {
    for(int i = 0; i < countriesOwned->size(); ++i)
        cout <<  countriesOwned->at(i)->toString() << endl;
    cout << " " << endl;
}

// DICE METHODS
void Player::diceObject() {
    myDice.rollDice();
}

// CARD METHODS
// Method that adds cards

/*
void Player::addCards(Card *newCard) {
    cardsOwned->push.back(*newCard);
}

// Displayed the cards that is aquired by this player
void Player::collectionOfRiskCards() {
    for(int i = 0; i < cardsOwned->size(); ++i)
        cout <<  cardsOwned->at(i)->toString() << endl;
    cout << " " << endl;
} 
*/



