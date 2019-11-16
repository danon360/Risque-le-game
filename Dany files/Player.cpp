#include "Player.h"
//local
using namespace std;
using std::vector;

// Default Constructor
Player::Player() {
	ID = new int(-1);
	countriesOwned = new vector<Country*>;
	playerHand = new Hand;
	name = new string();
	myDice = new Dice();
	myCountry = new Country();
	hasConqueredThisTurn = new bool(false);
}

Player::Player(string* _name, int id, Map* map) {
	ID = new int(id);
	countriesOwned = new vector<Country*>;
	myCountry = new Country();
	playerHand = new Hand;
	name = _name;
	myDice = new Dice();
	gameMap = map;
	hasConqueredThisTurn = new bool(false);
}

// Destructor
Player::~Player() {
	delete myCountry;
	delete myDice;
	delete countriesOwned;

	myCountry = NULL;
	countriesOwned = NULL;
	myDice = NULL;

}

struct attackPossibilities {
	Country* source;
	vector<Country*>* destination;

};

// Attack Method
void Player::attack() {

	int sourceIndex;
	Country* source = nullptr;
	Country* destination = nullptr;
	vector<struct attackPossibilities*>* attackTree = new vector<struct attackPossibilities*>;

	std::cout << "************************************************************************" << std::endl;
	std::cout << "                      Attack : " << getName() << std::endl;
	std::cout << "************************************************************************" << std::endl;

	string willAttack;

	generateAttackTree(this, attackTree);

	if (attackTree->size() <= 0) { // if nothing in attack tree then you cannot attack this turn -> skip attack phase
		std::cout << "No armies in your countries can attack this turn.\n" << std::endl;
		return;
	}

	std::cout << "Do you want to attack? ";
	std::cin >> willAttack;
	std::cout << std::endl;

	while (willAttack.compare("yes") == 0) {

		
		source = chooseSourceCountry(source, attackTree, &sourceIndex);
		destination = chooseDestinationCountry(destination, attackTree, sourceIndex);
		fight(source, destination);

		std::cout << "Do you want to attack again? ";
		std::cin >> willAttack;
		std::cout << std::endl;

		attackTree->clear();
		deleteAttackTree(attackTree);
		attackTree = new vector<struct attackPossibilities*>;

		generateAttackTree(this, attackTree); // need to regenerate tree as countries can change ownership after a fight

		if (willAttack.compare("yes") != 0) { // delete heap-allocated attackTree if 'no' is selected
			deleteAttackTree(attackTree);
		}
	}

	std::cout << "Ending attack... proceeding to Reinforce phase.\n" << std::endl;
	deleteAttackTree(attackTree);
}

void Player::fight(Country* source, Country* destination) {

	// implement the rest of the fight mechanism
	Player* defender = static_cast<Player*>(destination->owner);
	int attackerRoll = 3;
	int defenderRoll = 2;
	int attackerTroopCount;
	int defenderTroopCount;

	string continueAttacking = "yes";

	while (destination->getTroopCount() > 0 && continueAttacking.compare("yes") == 0) {

		attackerTroopCount = source->getTroopCount();
		defenderTroopCount = destination->getTroopCount();

		// Rolling dice of attacking and defending players respectively
		cout << getName() << "'s turn to roll dice..." << endl;
		this->diceFacility(&attackerRoll, &attackerTroopCount);
		cout << " " << endl;

		cout << defender->getName() << "'s turn to roll dice..." << endl;
		defender->diceFacility(&defenderRoll, &defenderTroopCount);

		this->compareDiceObjects(defender, source, destination);

		
		if(destination->getTroopCount() > 0) {
			std::cout << "Do you want to keep attacking " << defender->getName() << " at " << destination->getName() << std::endl;
			cin >> continueAttacking;
			std::cout << std::endl;
		}
		else {
			break;
		}

		
	}

	// will change the owner and display victory message if troop count is 0.
	changeOwner(destination,source);
}

void Player::changeOwner(Country* conquered, Country* winner) {

	if (conquered->getTroopCount() <= 0) {
		int transfers;
		std::cout << "Glory to " << this->getName() << "!! " << conquered->getName() << " has been conquered!" << std::endl;
		conquered->setID(*this->getID());
		conquered->owner = this;
		*hasConqueredThisTurn = true; // this will get reset in the GameEngine main game loop
		cout << "Please select how many armies you'd like to transfer from " << winner->getName() << " to " << conquered->getName() << " (minimum: " << *this->myDice->numOfRolls <<", maximum: "<< winner->getTroopCount()-1<<  " )" << endl;
		cin >> transfers;
		while (cin.fail() || transfers < *this->myDice->numOfRolls || transfers >= winner->getTroopCount()) {
			cout << "Error: Invalid number. Please try again." << endl;
			cin >> transfers;
		}
		winner->addToTroopCount(-transfers);
		conquered->addToTroopCount(transfers);
	}

	;
}

Country* Player::chooseSourceCountry(Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int* sourceIndex) {

	const int minChoice = 1;
	const int maxChoice = attackTree->size();
	int userChoice;

	do {
		std::cout << "Which country do you want to attack from?" << std::endl;
		printSourceCountries(attackTree);
		std::cout << ">>> ";
		cin >> userChoice;
		while (std::cin.fail()) // some error check to ensure interger input
		{
			std::cout << "Invalid input: enter a country in range (" << minChoice << " to " << maxChoice << ")" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> userChoice;
		}
		std::cout << std::endl;
		// set the source index and country

	} while (userChoice < minChoice || userChoice >> maxChoice);

	eventualSource = attackTree->at(userChoice - 1)->source; // set the country
	*sourceIndex = userChoice - 1; // set the index of the chose country (used in chooseDestinationCountry())

	return eventualSource;
}

Country* Player::chooseDestinationCountry(Country* eventualDestination, vector<struct attackPossibilities*>* attackTree, int sourceIndex) {

	Country* source = attackTree->at(sourceIndex)->source;

	const int minChoice = 1;
	const int maxChoice = source->getAdjacencyList()->size();
	int userChoice;

	do {
		std::cout << "Attacking from " << source->getName() << ". Which country do you want to attack?" << std::endl;
		printDestinationCountries(attackTree, sourceIndex);
		std::cout << ">>> ";
		cin >> userChoice;
		while (std::cin.fail()) // some error check to ensure interger input
		{
			std::cout << "Invalid input: enter a country in range (" << minChoice << " to " << maxChoice << ")" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> userChoice;
		}
		std::cout << std::endl;

		// set the destination to what user selected
		eventualDestination = attackTree->at(sourceIndex)->destination->at(userChoice - 1);

	} while (userChoice < minChoice || userChoice > maxChoice);

	return eventualDestination;
}

void Player::deleteAttackTree(vector<struct attackPossibilities*>* attackTree) {

	for (int i = 0; i < attackTree->size(); ++i) {
		delete attackTree->at(i);
	}
}

void Player::generateAttackTree(Player* player, vector<struct attackPossibilities*>* attackTree) {

	vector<Country*>* owned = player->getCountriesOwned();

	Country* source;

	for (int i = 0; i < owned->size(); ++i) {

		vector<Country*>* destinations = new vector<Country*>;
		source = owned->at(i);

		if (source->getTroopCount() > 1) { // first check: only owned countries with >1 troop can be source

			vector<Country*>* unvalidatedDestinations = source->getAdjacencyList();

			for (int j = 0; j < unvalidatedDestinations->size(); ++j) {

				Country* destination = unvalidatedDestinations->at(j);

				if (destination->getOwnerID() != source->getOwnerID()) { // second check: only countries not owned by me can be destinations
					destinations->push_back(destination);
				}
			}

		}
		if (destinations->size() > 0) { // only add a possibility if there are countries that can be attacked
			struct attackPossibilities* possibility = new attackPossibilities{ source, destinations };
			attackTree->push_back(possibility);
		}

	}

}

void Player::printSourceCountries(vector<struct attackPossibilities*>* attackTree) {

	for (int i = 0; i < attackTree->size(); ++i) {
		std::cout << i + 1 << ": " << attackTree->at(i)->source->toString() << std::endl; // print each valid source country
	}
}

void Player::printDestinationCountries(vector<struct attackPossibilities*>* attackTree, int sourceIndex) {

	struct attackPossibilities* current = attackTree->at(sourceIndex);

	vector<Country*>* destinationOptions = current->destination;

	for (int i = 0; i < destinationOptions->size(); ++i) {
		std::cout << (i + 1) << ": " << destinationOptions->at(i)->toString() << std::endl;
	}
}

void Player::setTroopCount(int troop, Country* country) {
	country->setTroopCount(troop);
}

int Player::getTroopCount(Country* country) {
	return country->getTroopCount();
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
		std::cout << i + 1 << ". " << countries->at(i)->toString() << std::endl;
	}
	std::cout << std::endl;
	std::cout << ">>> ";

	do {

		std::cin >> userChoice;
		while (std::cin.fail())// || (nArmies < 1) || nArmies > remainingArmies)
		{
			std::cout << "Invalid input: enter a country in range above." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> userChoice;
		}
		std::cout << std::endl;

	} while ((userChoice < 1) || (userChoice > countries->size()));
	return countries->at(userChoice - 1);
}


int Player::selectArmiesToReinforce(Country& source, int remainingArmies) {
	int nArmies;

	std::cout << source.getName() << " has " << source.getTroopCount() << " armies." << std::endl;
	std::cout << "Enter the number of armies you want to move to " << source.getName() << " (max " << remainingArmies << ")." << std::endl;

	std::cout << ">>> ";

	std::cin >> nArmies;
	while (std::cin.fail())// || (nArmies < 1) || nArmies > remainingArmies)
	{
		std::cout << "Invalid input: must be a number between 0 and " << remainingArmies << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> nArmies;
	}
	std::cout << std::endl;

	return nArmies;
}


int Player::continentBonus() {

	int bonusTally = 0;

	vector<int> continentCounter(gameMap->continents->size());

	for (int i = 0; i < continentCounter.size(); i++) {
		continentCounter.at(i) = 0;
	}
	int h;
	for (int i = 0; i < getCountriesOwned()->size(); i++) {
		h = countriesOwned->at(i)->getContinentNumber();
		continentCounter.at(h);
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

	std::cout << "**********************************************************************************" << std::endl;
	std::cout << "                               Reinforce : " << getName() << std::endl;
	std::cout << "**********************************************************************************" << std::endl;

	if (playerHand->size() > 4) {

		while (playerHand->size() > 4) { // to cover the case of killing off other players and getting a ton of cards
			cout << " You have more than 4 cards so you have to exchange " << endl;
			armiesFromExchange = playerHand->exchange();
		}
	}
	else if (playerHand->size() > 2) {
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
				std::cout << c->getName() << " now has " << c->getTroopCount() << " armies after reinforcing. " << std::endl;
			}
		}
		totalArmies -= armies;
		std::cout << std::endl;


	} while (totalArmies > 0);

}

bool Player::equals(Player* other) {
	return (*ID == *(other->getID()));
}

// COUNTRY METHODS
// Method that adds countries
void Player::addCountries(Country* country) {
	countriesOwned->push_back(country);
}

// Displays the countries owned by this player
void Player::collectionOfCountries() {
	for (int i = 0; i < countriesOwned->size(); ++i)
		cout << countriesOwned->at(i)->toString() << endl;
	cout << " " << endl;
}

void Player::fortify() {

	std::cout << "************************************************************************" << std::endl;
	std::cout << "                      Fortify : " << getName() << std::endl;
	std::cout << "************************************************************************" << std::endl;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip endline from previous 'cin'

	string answer;

	// does user want to fortify this turn? -----------------------------------------------------------------

	std::cout << "Do you want to fortify (yes/no)? ";
	cin >> answer;

	if (answer.compare("no") == 0 || answer.compare("NO") == 0)
		return;

	// get the country to move troops from -----------------------------------------------------------------

	vector<Country*> validMoveCountries;

	for (int i = 0; i < countriesOwned->size(); ++i) {

		Country* current = countriesOwned->at(i);

		if (current->getTroopCount() > 1) {
			validMoveCountries.push_back(current);
		}
	}

	for (int i = 0; i < validMoveCountries.size(); ++i) {
		std::cout << i + 1 << ": " << validMoveCountries.at(i)->toString() << std::endl;
	}

	int input = 0;

	std::cout << std::endl << "Please select the country you want to move armies from.\n";
	std::cout << ">>> ";
	std::cout << std::endl;

	cin >> input;
	//in case the user proviedes an invalid input or out of range
	while (std::cin.fail() || input < 1 || input > validMoveCountries.size())
	{
		std::cout << "Invalid input, please choose a number in the range" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}

	Country* countryFrom = validMoveCountries.at(input - 1);

	// get country to move to -------------------------------------------------------------------------------

	Country* countryTo;

	validMoveCountries.clear();

	vector<Country*>* neighbours = countryFrom->getAdjacencyList();

	for (int i = 0; i < neighbours->size(); ++i) {

		// each neigbour of a country that I own
		Country* current = neighbours->at(i);

		if (this->equals(static_cast<Player*>(current->owner))) {
			validMoveCountries.push_back(current);
		}
	}

	std::cout << "Please select a destination country to move troop to (moving from: " << countryFrom->getName() << "):" << std::endl;

	std::cout << std::endl;
	for (int i = 0; i < validMoveCountries.size(); ++i) {
		std::cout << i + 1 << ": " << validMoveCountries.at(i)->toString() << std::endl;
	}

	std::cout << ">>> ";
	cin >> input;
	//in case the user proviedes an invalid input or out of range
	while (std::cin.fail() || input < 1 || input > validMoveCountries.size())
	{
		std::cout << "Invalid input, please choose a number in the range" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}
	std::cout << std::endl;

	countryTo = validMoveCountries.at(input - 1);

	//  get troop count to move ------------------------------------------------------------------------------------

	int maxTroopsToMove = countryFrom->getTroopCount() - 1;

	std::cout << "How many troops to move (you can move up to " << maxTroopsToMove << " troops)" << std::endl;
	std::cout << ">>> ";
	cin >> input;
	//in case the user proviedes an invalid input or out of range
	while (std::cin.fail() || input < 0 || input > maxTroopsToMove)
	{
		std::cout << "Invalid input, please choose a number in the range" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}
	std::cout << std::endl;

	countryTo->addToTroopCount(input);
	countryFrom->addToTroopCount(-input);

	std::cout << "You moved " << input << " troops from " << countryFrom->getName() << " to "
		<< countryTo->getName() << std::endl << std::endl;

}


// DICE METHODS
void Player::diceFacility(int* maxRoll, int* numOfArmies) {
	myDice->rollDice(maxRoll, numOfArmies);
}

void Player::compareDiceObjects(Player* player, Country* attackingCountry, Country* defendingCountry) {

	int numDiceToCompare = std::min(*this->myDice->numOfRolls, *player->myDice->numOfRolls); // take the min to compare that amount of dice
	int* attackerDice = this->myDice->container;
	int* defencerDice = player->myDice->container;


	for (int i = 0; i < numDiceToCompare; ++i) {
		if (attackerDice[i] > defencerDice[i]) {
			defendingCountry->addToTroopCount(-1);
			cout << player->getName() << " has lost this round and loses one army " << endl;
		}
		else {
			attackingCountry->addToTroopCount(-1);
			cout << this->getName() << " has lost this round and loses one army " << endl;
		}
	}
}



