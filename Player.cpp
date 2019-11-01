#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include <iostream>
using namespace std;
using std::vector;

// Default Constructor
Player::Player() {
    countriesOwned = new vector<Country*>;
    //*name = " ";
    //cardsOwned = new vector<Card*>;
	//    Hand* playerHand;

}

// Destructor
Player::~Player() {
    
    delete countriesOwned;
    countriesOwned = NULL;
    
    
   // delete cardsOwned;
   // cardsOwned = NULL;
    
}


vector<Country*>* Player::getCountriesOwned()
{
	return this->countriesOwned;
}

Country Player::selectCountry(std::vector<Country> countries) {

	int userChoice;
	std::cout << "Source countries with available target countries:" << std::endl;

	for (int i = 0; i < countries.size(); i++) {
		std::cout << i + 1 << ". " << countries[i].getName() << std::endl;
	}
	std::cout << std::endl;
	std::cout << ">>> ";

	do {
		std::cin >> userChoice;
	} while ((userChoice < 1) || (userChoice > countries.size()));

	return countries[userChoice - 1];
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


void Player::reinforce(Player* player) {

	Player player = *player;

	int armiesFromExchange = playerHand->exchange();

	int armiesFromCountry = std::max((int)countriesOwned->size() / 3, 3);

	int armiesFromContinent;

	int totalArmies = armiesFromCountry + armiesFromExchange + armiesFromContinent;

	while (totalArmies > 0) {

		// Select country to reinforce
		std::cout << "\nYou have " << totalArmies << " remaining soldiers to add. ";
		std::cout << "Please select the country you would like to add soldiers to.\n";

		Country country = selectCountry(&player->getCountriesOwned);

		// Select number of armies to reinforce for the selected country
		int armies = selectArmiesToReinforce(country, totalArmies);

		for (auto& c : player->getCountriesOwned) {
			if (c.getName() == country.getName()) {
				c.increaseArmiesBy(armies);
				std::cout << c.getName() << " now has " << c.getArmies() << " armies after reinforcing. " << std::endl;
			}
		}
		totalArmies -= armies;
	}

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

void Player::attack() {
    // Player Decides if it will attack or not = Boolean variable and a loop
    // Select your own country (Must have 2 armies), Select neighbouring country to attack
    // 
    
    
    
   
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



