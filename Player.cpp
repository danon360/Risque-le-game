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

void Player::addACountry(Country* toAdd) {
	countriesOwned->push_back(toAdd);
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

	bool continueAttacking = strategy->attackDecision(this);
    
     Notify(*this->getID(), "Attacking", " and selecting countries to attack from");

	while (continueAttacking) {
		
		// find the country to attack from
		source = strategy->chooseSourceCountryToAttackFrom(this, source, attackTree, &sourceIndex);
		// find the country to attack
		destination = strategy->chooseDestinationCountryToAttack(this, destination, attackTree, sourceIndex);
		// start the fight sequence
		fight(source, destination);

		// destroy data structure and regenerate it after the fight (will have change if a country changed hands)
		attackTree->clear();
		deleteAttackTree(attackTree);
		attackTree = new vector<struct attackPossibilities*>;
		generateAttackTree(this, attackTree); // need to regenerate tree as countries can change ownership after a fight

		// does user want to attack another country?
		continueAttacking = strategy->continueAttacking(this);
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

	bool continueAttacking = true;

	while (destination->getTroopCount() > 0 && continueAttacking) {

		attackerTroopCount = source->getTroopCount();
		defenderTroopCount = destination->getTroopCount();

		// Rolling dice of attacking and defending players respectively
		cout << getName() << "'s turn to roll dice..." << endl;
		int numAttackDice = strategy->attackerChooseDice(this, defender, source, destination);
		this->diceFacility(&attackerRoll, &attackerTroopCount, numAttackDice);
		cout << " " << endl;

		cout << defender->getName() << "'s turn to roll dice..." << endl;
		int numDefendDice = strategy->defenderChooseDice(defender, this, destination, source);
		defender->diceFacility(&defenderRoll, &defenderTroopCount, numDefendDice);

		this->compareDiceObjects(defender, source, destination);
		
		if(destination->getTroopCount() > 0) {

			continueAttacking = strategy->keepFightingAtCountry(this, defender, source, destination);

		}
		else {
			std::cout << getName() << " does not have enough armies to keep attacking " << defender->getName() << " at " << destination->getName() << std::endl;
			break;
		}
	}

	// will change the owner and display victory message if troop count is 0.
	if (destination->getTroopCount() <= 0) {
		changeOwner(destination, source);
	}
}

void Player::changeOwner(Country* conquered, Country* winner) {

	int armiesToTransfer;

	std::cout << "\n***Glory to " << this->getName() << "!! " << conquered->getName() << " has been conquered!\n" << std::endl;

	conquered->setID(*this->getID());
	conquered->owner = this;
	this->addACountry(conquered);

	*hasConqueredThisTurn = true; // this will get reset in the GameEngine main game loop

	armiesToTransfer = strategy->howManyTroopsToTranferAfterAWin(this, conquered, winner);
	
	winner->addToTroopCount(-armiesToTransfer);
	conquered->addToTroopCount(armiesToTransfer);
}

void Player::deleteAttackTree(vector<struct attackPossibilities*>* attackTree) {

	for (int i = 0; i < attackTree->size(); ++i) {
		delete attackTree->at(i);
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

void Player::setTroopCount(int troop, Country* country) {
	country->setTroopCount(troop);
}

int Player::getTroopCount(Country* country) {
	return country->getTroopCount();
}

Hand* Player::getHand() {
	return playerHand;
}

vector<Country*>* Player::getCountriesOwned() {
	return countriesOwned;
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

	// index 0 will hold the number of countries owned that are of continent 0
	vector<int> continentCounter(gameMap->continents->size());

	// initialize the vector
	for (int i = 0; i < continentCounter.size(); i++) {
		continentCounter.at(i) = 0;
	}

	int h;

	for (int i = 0; i < getCountriesOwned()->size(); i++) {
		// hold the continent id of this country
		h = countriesOwned->at(i)->getContinentNumber();
		// for each country in continent h, add 1 to the counter
		++continentCounter.at(h);
	}

	// check the counters vs the #of countries in that continent, if equal then player owns that continent and get the bonus
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

	std::cout << "**********************************************************************************" << std::endl;
	std::cout << "                               Reinforce : " << getName() << std::endl;
	std::cout << "**********************************************************************************" << std::endl;

     Notify(*this->getID(), "Reinforcing", "");
    
	// Strategy pattern decision point: Does player want to exchange cards this turn
	armiesFromCountry = strategy->doExchangeOfCards(this);

	armiesFromCountry = std::max((int)countriesOwned->size() / 3, 3);

	armiesFromContinent = continentBonus();

	int totalArmies = armiesFromCountry + armiesFromExchange + armiesFromContinent;

	// Strategy pattern decision point: what Country to assign the bonus troop
	strategy->whereToAssignReinforceArmies(this, totalArmies);

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


	// does user want to fortify this turn? -----------------------------------------------------------------
	if (strategy->fortifyDecision(this)) {
        
         Notify(*this->getID(), "Fortifying", "");

		// get the country to move troops from -----------------------------------------------------------------
		Country* countryFrom = strategy->whereToFortifyFrom(this);
		if (countryFrom == nullptr) {
			std::cout << "No source country for fortify." << std::endl;
			return;
		}

		Country* countryTo = strategy->whereToFortifyTo(this, countryFrom);
		// get country to move to -------------------------------------------------------------------------------
		if (countryTo == nullptr) {
			std::cout << "No country can be fortied." << std::endl;
			return;
		}
		

		//  get troop count to move ------------------------------------------------------------------------------------
		int armiesMoved = strategy->howManyArmiesToFortifyWith(this, countryFrom, countryTo);
		std::cout << this->getName() << " moved " << armiesMoved << " armies from " << countryFrom->getName() << " to "
			<< countryTo->getName() << std::endl << std::endl;
	}
	else {
		std::cout << this->getName() << " chose not to fortify this turn." << std::endl;
	}
}


// DICE METHODS
void Player::diceFacility(int* maxRoll, int* numOfArmies, int numDiceToRoll) {
	
	myDice->rollDice(maxRoll, numOfArmies, numDiceToRoll);
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

/*************************************************************************************
								  PlayerStrategies
**************************************************************************************/

// Constructors / Destructors --------------------------------------------------------
PlayerStrategies::PlayerStrategies() {

}

PlayerStrategies::~PlayerStrategies() {

}

// Setup methods ---------------------------------------------------------------------
void PlayerStrategies::printSourceCountries(vector<struct attackPossibilities*>* attackTree) {

	for (int i = 0; i < attackTree->size(); ++i) {
		std::cout << i + 1 << ": " << attackTree->at(i)->source->toString() << std::endl; // print each valid source country
	}
}

void PlayerStrategies::printDestinationCountries(vector<struct attackPossibilities*>* attackTree, int sourceIndex) {

	struct attackPossibilities* current = attackTree->at(sourceIndex);

	vector<Country*>* destinationOptions = current->destination;

	for (int i = 0; i < destinationOptions->size(); ++i) {
		std::cout << (i + 1) << ": " << destinationOptions->at(i)->toString() << std::endl;
	}
}

// Reinforce methods -----------------------------------------------------------------


// Attack methods --------------------------------------------------------------------


// Fortify methods -------------------------------------------------------------------


/*************************************************************************************
								  PlayerStrategies
**************************************************************************************/

// Constructors / Destructors --------------------------------------------------------
HumanStrategy::HumanStrategy() {

}


HumanStrategy::~HumanStrategy() {

}

// Setup methods ---------------------------------------------------------------------


// Reinforce methods -----------------------------------------------------------------

int HumanStrategy::doExchangeOfCards(Player* player) {

	int armiesFromExchange = 0;
	int user;
	Hand* playerHand = player->getHand();

	if (playerHand->size() > 4) {

		while (playerHand->size() > 4) { // to cover the case of killing off other players and getting a ton of cards
			cout << " You have more than 4 cards so you have to exchange " << endl;
			armiesFromExchange = playerHand->exchange();
		}
	}
	else if (playerHand->isExchangePossible()) {
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

	return armiesFromExchange;
}

void HumanStrategy::whereToAssignReinforceArmies(Player* player, int totalArmies) {

	do {

		// Select country to reinforce
		std::cout << "\nYou have " << totalArmies << " remaining soldiers to add. ";
		std::cout << "Please select the country you would like to add soldiers to.\n";

		Country* country = player->selectCountry(player->getCountriesOwned());

		// Select number of armies to reinforce for the selected country
		int armies = player->selectArmiesToReinforce(*country, totalArmies);

		vector<Country*>* cntry = player->getCountriesOwned();


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

// Attack methods --------------------------------------------------------------------

bool HumanStrategy::attackDecision(Player* player) {

	string willAttack;

	std::cout << "Do you want to attack? ";
	std::cin >> willAttack;
	std::cout << std::endl;

	if (willAttack.compare("yes") == 0 || willAttack.compare("YES") == 0 || willAttack.compare("y") == 0 || willAttack.compare("Y") == 0)
		return true;
	else
		return false;
}

Country* HumanStrategy::chooseSourceCountryToAttackFrom(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int* sourceIndex) {

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

	} while (userChoice < minChoice || userChoice >> maxChoice);

	// set the source index and country
	eventualSource = attackTree->at(userChoice - 1)->source; // set the country
	*sourceIndex = userChoice - 1; // set the index of the chose country (used in chooseDestinationCountry())

	return eventualSource;
}

Country* HumanStrategy::chooseDestinationCountryToAttack(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int sourceIndex) {

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

	} while (userChoice < minChoice || userChoice > maxChoice);

	// set the destination to what user selected
	Country* eventualDestination = attackTree->at(sourceIndex)->destination->at(userChoice - 1);

	return eventualDestination;
}

int HumanStrategy::attackerChooseDice(Player* attacker, Player* defender, Country* source, Country* destination) {

	int numDice = std::min(3, source->getTroopCount()); // hard-coded for the attack->Risk rules: attacker has max = 3 dice
	int diceToRoll;

	std::cout << "Roll from 1 to " << numDice << " dice (you have " << source->getTroopCount() << " armies)" << std::endl;
	cin >> diceToRoll;

	while (std::cin.fail() || diceToRoll < 1 || diceToRoll > numDice)
	{
		std::cout << "Error: Roll from 1 to " << numDice << " dice (you have " << source->getTroopCount() << " armies)" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> diceToRoll;
	}
	std::cout << std::endl;

	return diceToRoll;
}

int HumanStrategy::defenderChooseDice(Player* defender, Player* attacker, Country* source, Country* destination) {

	const int numDice = std::min(2, destination->getTroopCount()); // hard-coded for the attack->Risk rules: attacker has max = 3 dice
	int diceToRoll;

	std::cout << "Roll from 1 to " << numDice << " dice (you have " << destination->getTroopCount() << " armies)" << std::endl;
	cin >> diceToRoll;

	while (std::cin.fail() || diceToRoll < 1 || diceToRoll > numDice)
	{
		std::cout << "Error: Roll from 1 to " << numDice << " dice (you have " << destination->getTroopCount() << " armies)" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> diceToRoll;
	}
	std::cout << std::endl;

	return diceToRoll;
}

bool HumanStrategy::continueAttacking(Player* player) {

	string willAttack;

	std::cout << "Do you want to attack again? ";
	std::cin >> willAttack;
	std::cout << std::endl;

	if (willAttack.compare("yes") == 0 || willAttack.compare("YES") == 0 || willAttack.compare("y") == 0 || willAttack.compare("Y") == 0)
		return true;
	else
		return false;

}

int HumanStrategy::howManyTroopsToTranferAfterAWin(Player* player, Country* conquered, Country* winner) {

	const int minArmiesToTransfer = 1;
	const int maxArmiesToTransfer = winner->getTroopCount() - 1;
	int armiesToTransfer;

	cout << "Please select how many armies you'd like to transfer from " << winner->getName() << " to " << conquered->getName()
		<< " (minimum: " << 1 << ", maximum: " << winner->getTroopCount() - 1 << " )" << endl;
	cin >> armiesToTransfer;

	while (cin.fail() || armiesToTransfer < minArmiesToTransfer || armiesToTransfer >= maxArmiesToTransfer) {
		cin.clear();
		cout << "Error: Invalid number. Please try again." << endl;
		cin >> armiesToTransfer;
	}

	return armiesToTransfer;
}

bool HumanStrategy::keepFightingAtCountry(Player* attacker, Player* defender, Country* source, Country* destination) {

	string continueAttacking;

	std::cout << "Do you want to keep attacking " << defender->getName() << " at " << destination->getName() << std::endl;
	cin >> continueAttacking;
	std::cout << std::endl;

	if (continueAttacking.compare("yes") == 0 || continueAttacking.compare("YES") == 0 || continueAttacking.compare("y") == 0 || continueAttacking.compare("Y") == 0)
		return true;
	else
		return false;
}

// Fortify methods -------------------------------------------------------------------

bool HumanStrategy::fortifyDecision(Player* player) {
	
	string answer;

	std::cout << "Do you want to fortify (yes/no)? ";
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip endline from previous 'cin'
	cin >> answer;

	if (answer.compare("no") == 0 || answer.compare("NO") == 0)
		return false;
	else
		return true;
}

Country* HumanStrategy::whereToFortifyFrom(Player* player) {

	vector<Country*> validMoveCountries;

	vector<Country*>* playersOwnedCountries = player->getCountriesOwned();
	for (int i = 0; i < playersOwnedCountries->size(); ++i) {

		Country* current = playersOwnedCountries->at(i);

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
	//in case the user provides an invalid input or out of range
	while (std::cin.fail() || input < 1 || input > validMoveCountries.size())
	{
		std::cout << "Invalid input, please choose a number in the range" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;
	}

	return validMoveCountries.at(input - 1);
}

Country* HumanStrategy::whereToFortifyTo(Player* player, Country* countryFrom) {

	int input;
	vector<Country*> validMoveCountries;
	vector<Country*>* neighbours = countryFrom->getAdjacencyList();

	for (int i = 0; i < neighbours->size(); ++i) {

		// each neighbour of a country that I own
		Country* current = neighbours->at(i);

		if (player->equals(static_cast<Player*>(current->owner))) {
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

	return validMoveCountries.at(input - 1);
}

int HumanStrategy::howManyArmiesToFortifyWith(Player* player, Country* countryFrom, Country* countryTo) {

	int input;
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

	return input;
}

/*************************************************************************************
								  AgressiveStrategy
**************************************************************************************/

// Constructors / Destructors --------------------------------------------------------
AgressiveStrategy::AgressiveStrategy() {

}

AgressiveStrategy::~AgressiveStrategy() {

}

// Setup methods ---------------------------------------------------------------------


// Reinforce methods -----------------------------------------------------------------
int AgressiveStrategy::doExchangeOfCards(Player* player) {

	int armiesFromExchange = 0;

	Hand* playerHand = player->getHand();

	if (playerHand->size() > 4) {

		while (playerHand->size() > 4) { // to cover the case of killing off other players and getting a ton of cards
			cout << " You have more than 4 cards so you have to exchange." << endl;
			armiesFromExchange = playerHand->exchange();
		}
	}
	else if (playerHand->isExchangePossible()) {
		cout << " You have exchanged cards." << endl;
		armiesFromExchange = playerHand->exchange();
	}

	return armiesFromExchange;
}

// Attack methods --------------------------------------------------------------------
bool AgressiveStrategy::attackDecision(Player* player) {
	return true; // Blood for the Blood God!
}

Country* AgressiveStrategy::chooseSourceCountryToAttackFrom(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int* sourceIndex) {

	vector<Country*>* owned = player->getCountriesOwned();

	bool foundMaxCountryBorderingEnemy = false;

	Country* maxTroopCountry;
	vector<Country*>* neighbours;

	/*	NOTE: this is incomplete, it should find the max country and check if there are enemies
		if there are some, return the max country. If not, find the second max and do same check (not implemented).
	*/
	maxTroopCountry = findMaxTroopCountry(owned); // find your country with the most troops
	neighbours = maxTroopCountry->getAdjacencyList();

	for (int i = 0; i < neighbours->size(); ++i) {

		Country* potentialEnemy = neighbours->at(i);

		if (potentialEnemy->getOwnerID() != *player->getID()) { // ie. an enemy country
			foundMaxCountryBorderingEnemy = true;
		}
	}
	
	if (foundMaxCountryBorderingEnemy)
		return maxTroopCountry;
	else
		return nullptr;
}

Country* AgressiveStrategy::chooseDestinationCountryToAttack(Player* player, Country* eventualSource, vector<struct attackPossibilities*>* attackTree, int sourceIndex) {

	std::vector<Country*>* neighbours = eventualSource->getAdjacencyList();
	std::vector<Country*> enemies;

	Country* possibleEnemy;

	for (int i = 0; i < neighbours->size(); ++i) {

		possibleEnemy = neighbours->at(i);

		if (eventualSource->getID() != possibleEnemy->getID()) {
			enemies.push_back(possibleEnemy);
		}

	}

	Country* toAttack = findMinTroopCountry(&enemies);


	return toAttack;
}


int AgressiveStrategy::attackerChooseDice(Player* attacker, Player* defender, Country* source, Country* destination) {
	return std::min(3, source->getTroopCount()); // as many dice as he can... always!
}

int AgressiveStrategy::defenderChooseDice(Player* defender, Player* attacker, Country* source, Country* destination) {
	return std::min(2, source->getTroopCount()); // as many dice as he can... always!
}

bool AgressiveStrategy::continueAttacking(Player* player) {
	return true;
}

bool AgressiveStrategy::keepFightingAtCountry(Player* attacker, Player* defender, Country* source, Country* destination) {
	return true;
}

int AgressiveStrategy::howManyTroopsToTranferAfterAWin(Player* player, Country* conquered, Country* winner) {
	return winner->getTroopCount() - 1;
}

// Fortify methods -------------------------------------------------------------------

bool AgressiveStrategy::fortifyDecision(Player* player) {
	return true;
}

int AgressiveStrategy::howManyArmiesToFortifyWith(Player* player, Country* countryFrom, Country* countryTo) {
	return countryFrom->getTroopCount() - 1;
}

Country* AgressiveStrategy::whereToFortifyFrom(Player* player) {

	// get the country with the min number of troops
	Country* fortifiee = findMinTroopCountry(player->getCountriesOwned());

	// get the list of adjacent countries to it
	vector<Country*>* candidateToReinforceMax = fortifiee->getAdjacencyList();

	// take the neighbour with the max troops to reinforce
	Country* fortifier = findMaxTroopCountry(candidateToReinforceMax);

	return fortifier; // this can be nullptr
}

Country* AgressiveStrategy::whereToFortifyTo(Player* player, Country* countryFrom) {
	return findMaxTroopCountry(countryFrom->getAdjacencyList()); // this can be nullptr
}

// Private helper methods ------------------------------------------------------------

Country* AgressiveStrategy::findMinTroopCountry(vector<Country*>* validMoveCountries) {

	Country* minTroopCountry = validMoveCountries->at(0);

	for (int i = 1; i < validMoveCountries->size(); ++i) {

		Country* temp = validMoveCountries->at(i);

		if (temp->getTroopCount() < minTroopCountry->getTroopCount())
			minTroopCountry = temp;
	}

	return minTroopCountry;
}

Country* AgressiveStrategy::findMaxTroopCountry(vector<Country*>* validMoveCountries) {

	Country* minTroopCountry = validMoveCountries->at(0);

	for (int i = 1; i < validMoveCountries->size(); ++i) {

		Country* temp = validMoveCountries->at(i);

		if (temp->getTroopCount() > minTroopCountry->getTroopCount())
			minTroopCountry = temp;
	}

	return minTroopCountry;
}


/*************************************************************************************
								  BenevolentStrategy
**************************************************************************************/

// Constructors / Destructors --------------------------------------------------------
BenevolentStrategy::BenevolentStrategy() {

}

BenevolentStrategy::~BenevolentStrategy() {

}

// Setup methods ---------------------------------------------------------------------


// Reinforce methods -----------------------------------------------------------------
int BenevolentStrategy::doExchangeOfCards(Player* player) {

	int armiesFromExchange = 0;

	Hand* playerHand = player->getHand();

	if (playerHand->size() > 4) {

		while (playerHand->size() > 4) { // to cover the case of killing off other players and getting a ton of cards
			cout << " You have more than 4 cards so you have to exchange." << endl;
			armiesFromExchange = playerHand->exchange();
		}
	}
	else if (playerHand->isExchangePossible()) {
		cout << " You have exchanged cards." << endl;
		armiesFromExchange = playerHand->exchange();
	}

	return armiesFromExchange;
}

// Attack methods --------------------------------------------------------------------
bool BenevolentStrategy::attackDecision(Player* player) {
	return false; // I'm too young to die!
}



int BenevolentStrategy::attackerChooseDice(Player* attacker, Player* defender, Country* source, Country* destination) {
	return std::min(1, source->getTroopCount()); // as few dice as he can... bring our boys home!
}

int BenevolentStrategy::defenderChooseDice(Player* defender, Player* attacker, Country* source, Country* destination) {
	return std::min(1, source->getTroopCount()); // as few dice as he can... bring our boys home!
}

bool BenevolentStrategy::continueAttacking(Player* player) {
	return false;
}

bool BenevolentStrategy::keepFightingAtCountry(Player* attacker, Player* defender, Country* source, Country* destination) {
	return false;
}

int BenevolentStrategy::howManyTroopsToTranferAfterAWin(Player* player, Country* conquered, Country* winner) {
	return winner->getTroopCount() - 1;
}

// Fortify methods -------------------------------------------------------------------

bool BenevolentStrategy::fortifyDecision(Player* player) {
	return true;
}

int BenevolentStrategy::howManyArmiesToFortifyWith(Player* player, Country* countryFrom, Country* countryTo) {
	return countryFrom->getTroopCount() - 1;
}

Country* BenevolentStrategy::whereToFortifyFrom(Player* player) {

	// get the country with the max number of troops
	Country* fortifiee = findMinTroopCountry(player->getCountriesOwned());

	// get the list of adjacent countries to it
	vector<Country*>* candidatesToReinforceMax = fortifiee->getAdjacencyList();

	// take the neighbour with the max troops to reinforce
	Country* fortifier = findMaxTroopCountry(candidatesToReinforceMax);

	return fortifier; // this can be nullptr
}

Country* BenevolentStrategy::whereToFortifyTo(Player* player, Country* countryFrom) {
	return findMinTroopCountry(countryFrom->getAdjacencyList()); // this can be nullptr
}

// Private helper methods ------------------------------------------------------------

Country* BenevolentStrategy::findMinTroopCountry(vector<Country*>* validMoveCountries) {

	Country* minTroopCountry = validMoveCountries->at(0);

	for (int i = 1; i < validMoveCountries->size(); ++i) {

		Country* temp = validMoveCountries->at(i);

		if (temp->getTroopCount() < minTroopCountry->getTroopCount())
			minTroopCountry = temp;
	}

	return minTroopCountry;
}

Country* BenevolentStrategy::findMaxTroopCountry(vector<Country*>* validMoveCountries) {

	Country* minTroopCountry = validMoveCountries->at(0);

	for (int i = 1; i < validMoveCountries->size(); ++i) {

		Country* temp = validMoveCountries->at(i);

		if (temp->getTroopCount() > minTroopCountry->getTroopCount())
			minTroopCountry = temp;
	}

	return minTroopCountry;
}


