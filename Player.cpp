#include "Player.h"

using namespace std;
using std::vector;

// Default Constructor
Player::Player() {
	countriesOwned = new vector<Country*>;
	playerHand = new Hand;
	name = new string();
	Dice myDice;
}

Player::Player(string * _name, int id, Map* map) {
    countriesOwned = new vector<Country*>;
	playerHand = new Hand; 
	name = _name;
	Dice myDice; 
	gameMap = map;
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

void Player::setMap(Map* map) {
	gameMap = map;
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

	int bonusTally = 0;

	vector<int> continentCounter(gameMap->continents->size());

	for (int i = 0; i < continentCounter.size(); i++) {
		continentCounter[i] = 0;
	}

	for (int i = 0; i < getCountriesOwned()->size(); i++) {
		continentCounter[(countriesOwned->at(i)->getContinentNumber() - 1)]++;
	}

	for (int i = 0; i < continentCounter.size(); i++) {

		Continent* c = gameMap->continents->at(i);

		if (continentCounter.at(i) == c->countries->size()) {
			bonusTally += c->getTroopBonus();
		} 
		
	}

	return bonusTally;
}


void Player::reinforce() {

	int armiesFromExchange = 0;
	int armiesFromContinent = 0;
	int armiesFromCountry = 0;
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


	 armiesFromCountry = std::max((int)countriesOwned->size() / 3, 3);

	 armiesFromContinent = continentBonus();


	int totalArmies = armiesFromCountry + armiesFromExchange + armiesFromContinent;

	do {

		// Select country to reinforce
		std::cout << "\nYou have " << totalArmies << " remaining soldiers to add. ";
		std::cout << "Please select the country you would like to add soldiers to.\n";

		Country* country = selectCountry(getCountriesOwned());

		// Select number of armies to reinforce for the selected country
		int armies = selectArmiesToReinforce(*country, totalArmies);

		vector<Country*>* cntry = getCountriesOwned();

	
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
    //myDice->rollDice();
}


void Player::attack(Player* player) {
    // Player Decides if it will attack or not = Boolean variable and a loop
    // Select your own country (Must have 2 armies), Select neighbouring country to attack
    // 
    
    
    
   
 }

/*void Player::fortify(Player* player) {

	int armiesToMove;

	Country* countryFrom;
	do {
		cout << "Select a country to move armies from" << endl;
		 countryFrom = selectCountry(player->getCountriesOwned());

	} while (countryFrom->getTroopCount() > 1);

	armiesToMove = countryFrom->getTroopCount() - 1;

	Country* countryTo;

	cout << "Select a country to move armies to" << endl;
	countryTo = selectCountry(player->getCountriesOwned());


		vector <Country*>* cntry = countryFrom->getAdjacencyList();

	for (auto& c : *cntry) {
			if (c->getName() == countryTo->getName()) {

				c->addToTroopCount(armies);
				std::cout << c->getName() << " now has " << c->getTroopCount() << " armies after reinforcing. " << std::endl;
			}
		}





}*/






