#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include <iostream>
using namespace std;
using std::vector;

// Default Constructor
Player::Player() {

    countriesOwned = new vector<Country*>;
    name = new string();
	playerHand = new Hand; 
	Dice myDice; 

}

Player::Player(string* _name) {

	countriesOwned = new vector<Country*>;
	name = _name;
	playerHand = new Hand;
	Dice myDice;

}

Player::Player(vector<Country*>* playerCountries, Dice* playerDice, Hand* hand, string* playerName) {
	countriesOwned = playerCountries;
	myDice = playerDice;
	playerHand = hand;
	name = playerName;

}


// Destructor
Player::~Player() {
    
    delete countriesOwned;
    countriesOwned = NULL;
   
}

Hand* Player::getHand() {
	return playerHand;
}


vector<Country*>* Player::getCountriesOwned()
{
	return countriesOwned;
}

Country* Player::selectCountry(std::vector<Country*>* countries) {

	int userChoice;
	std::cout << "Source countries with available target countries:" << std::endl;

	for (int i = 0; i < countries->size(); i++) {
		std::cout << i + 1 << ". " << countries->at(i)->getName() << std::endl;
	}
	std::cout << std::endl;
	std::cout << ">>> ";

	do {
		std::cin >> userChoice;
	} while ((userChoice < 1) || (userChoice > countries->size()));
	return countries->at(userChoice - 1);
}


int Player::selectArmiesToReinforce( Country& source, int remainingArmies) {
	int nArmies;

	std::cout << source.getName() << " has " << source.getTroopCount() << " armies." << std::endl;
	std::cout << "Enter the number of armies you want to move to your target country." << std::endl;

	std::cout << ">>> ";

	do {
		std::cin >> nArmies;

	} while ((nArmies < 1) || nArmies > remainingArmies); 
		std::cin >> nArmies;
	
	return nArmies;
}
int Player::continentBonus() {

	vector<int> continentCntr();

}

void Player::reinforce(Player* player) {

	int armiesFromExchange=0;
	int user;

	if (playerHand->size() > 4) {

		cout << " You have more than 4 cards so you have to exchange " << endl;
		armiesFromExchange = playerHand->exchange();
	}
	else {
		do {
			cout << "Do you want to exchange? press 1 for Yes and 0 for NO" << endl;
			cin >> user;
			if (user == 0) {
				armiesFromExchange = 0;
			}
			if (user == 1) {
				armiesFromExchange = playerHand->exchange();
			}
		} while (user != 0 && user != 1); 
	}


	int armiesFromCountry = std::max((int)countriesOwned->size() / 3, 3);

	int armiesFromContinent=0;


	int totalArmies = armiesFromCountry + armiesFromExchange + armiesFromContinent;

	do {

		// Select country to reinforce
		std::cout << "\nYou have " << totalArmies << " remaining soldiers to add. ";
		std::cout << "Please select the country you would like to add soldiers to.\n";

		Country* country = selectCountry(player->getCountriesOwned());

		// Select number of armies to reinforce for the selected country
		int armies = selectArmiesToReinforce(*country, totalArmies);

		vector<Country*>* cntry = player->getCountriesOwned();

	
		for (auto& c : *cntry) {
			if (c->getName() == country->getName()) {
				c->addToTroopCount(armies);
				std::cout << c->getName() << " now has " << c->getTroopCount()<< " armies after reinforcing. " << std::endl;
			}
		}
		totalArmies -= armies;

		
	} while (totalArmies > 0);

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
    myDice->rollDice();
}


void Player::attack(Player* player) {
    // Player Decides if it will attack or not = Boolean variable and a loop
    // Select your own country (Must have 2 armies), Select neighbouring country to attack
    // 
    
    
    
   
 }







