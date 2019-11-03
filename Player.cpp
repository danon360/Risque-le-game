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

Player::Player(string* _name, int id, Map* map) {
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
		if ((userChoice < 1) || (userChoice > countries->size())) {
			cout << " Please enter a valid number " << endl;
		}
	} while ((userChoice < 1) || (userChoice > countries->size()));

	return countries->at(userChoice - 1);
}


int Player::selectArmiesToReinforce(Country& source, int remainingArmies) {
	int nArmies;

	std::cout << source.getName() << " has " << source.getTroopCount() << " armies." << std::endl;
	std::cout << "Enter the number of armies you want to move to your target country." << std::endl;

	std::cout << ">>> ";

	do {
		std::cin >> nArmies;
		if ((nArmies < 1) || nArmies > remainingArmies){
			cout << " Please select a valid armies number " << endl;
        }

	} while ((nArmies < 1) || nArmies > remainingArmies); 
	
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
		std::cout << "Please select the country you would like to add armies to.\n";

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
  
bool Player::equals(Player* other) {
	return (*other->getID() == *ID);
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

void Player::fortify() {

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip endline from previous 'cin'

	string answer;

	// does user want to fortify this turn? -----------------------------------------------------------------

	std::cout << "Do you want to fortify (yes/no)?" << std::endl;
	cin >> answer;

	if (answer.compare("no") || answer.compare("NO"))
		return;

	// get the country to move troops from -----------------------------------------------------------------

	vector<Country*> validMoveCountries;

	for (int i = 0; i < countriesOwned->size(); ++i) {

		Country * current = countriesOwned->at(i);

		if (current->getTroopCount() > 1) {
			validMoveCountries.push_back(current);
		}
	}

	for (int i = 0; i < validMoveCountries.size(); ++i) {
		std::cout << i+1 << ": " << validMoveCountries.at(i)->toString() << std::endl;
	}

	int input = 0;

	std::cout << "Please select the country you would like to add soldiers to.\n";
	cin >> input;
	//in case the user proviedes an invalid input or out of range
	while (std::cin.fail() || input < 1 || input > validMoveCountries.size())
	{
		std::cout << "Invalid input, please choose a number in the range" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}

	Country* countryFrom = validMoveCountries.at(input-1);

	// get country to move to -------------------------------------------------------------------------------

	Country* countryTo;

	validMoveCountries.clear();

	for (int i = 0; i < countryFrom->getAdjacencyList()->size(); ++i) {

		Country * current = countriesOwned->at(i);

		if (equals(static_cast<Player*>(current->owner))) {
			validMoveCountries.push_back(current);
		}
	}

	std::cout << "Please select a destination country to move ( moving from: " << countryFrom->getName() << " ):" << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < validMoveCountries.size(); ++i) {
		std::cout << i + 1 << ": " << validMoveCountries.at(i)->toString() << std::endl;
	}

	cin >> input;
	//in case the user proviedes an invalid input or out of range
	while (std::cin.fail() || input < 1 || input > validMoveCountries.size())
	{
		std::cout << "Invalid input, please choose a number in the range" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}

	countryTo = validMoveCountries.at(input - 1);

	//  get troop count to move ------------------------------------------------------------------------------------

	int maxTroopsToMove = countryFrom->getTroopCount() - 1;

	std::cout << "How many troops to move (you can move up to " << maxTroopsToMove << " troops)"  << std::endl;

	cin >> input;
	//in case the user proviedes an invalid input or out of range
	while (std::cin.fail() || input < 0 || input > maxTroopsToMove)
	{
		std::cout << "Invalid input, please choose a number in the range" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}

	countryTo->addToTroopCount(input);
	countryFrom->addToTroopCount(-input);

	std::cout << "You moved " << input << " troops from " << countryFrom->getName() << " to " 
		<< countryTo->getName() << std::endl;

}






