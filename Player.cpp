#include "Player.h"
//local
using namespace std;
using std::vector;

// Default Constructor
Player::Player() {
	countriesOwned = new vector<Country*>;
	playerHand = new Hand;
	name = new string();
	Dice myDice;
	myCountry = new Country();						  
}

Player::Player(string * _name, int id, Map* map) {
    countriesOwned = new vector<Country*>;
	myCountry = new Country();						  
	playerHand = new Hand; 
	name = _name;
	Dice myDice; 
	gameMap = map;
}


/*
Player::Player(vector<Country*>* playerCountries, Dice* playerDice, Hand* hand, string* playerName) {
	countriesOwned = playerCountries;
	myDice = playerDice;
	playerHand = hand;
	name = playerName;

}
*/

// Destructor
Player::~Player() {
    delete myCountry;
    delete myDice;
    delete countriesOwned;
    
    myCountry = NULL;
    countriesOwned = NULL;
    myDice = NULL;
   
}

// Attack Method
void Player::attack(){
    // Pointers willAttack decides if the player will attack or not
    Player* defendingPlayer;
    Country* defendingCountry;
    Country* attackingCountry;
    int* attackerRoll = new int(3);
    int* defenderRoll = new int(2);
    int* attackingArmies = new int();
    int* defendingArmies = new int();
    int* selectedAttackCountry = new int();
    int* selectedDefendCountry = new int();
    int* sizeOfNeighbours = new int();
    string* willAttack = new string();
    vector<Country *> *validAttackCountries = new vector<Country *>;
    vector<Country *> *validDefendCountries = new vector<Country *>;
    
    // Prompts the user for attack
    cout << "Do you want to attack? (yes/no): ";
    cin >> *willAttack;
    
    // Main attack loop
    while (*willAttack == "yes") {
        cout << "Attacking..." << endl;;
        
        /** ----- SELECTING COUNTRIES TO ATTACK FROM AND THE DEFENDING COUNTRY -----*/
        // ----- SELECTING THE VALID COUNTRY TO ATTACK FROM -----
        
        cout << "These are the countries that you can attack from: " << endl;
        
        // Initializing all the valid attacking countries and display them
        for(int i = 0; i < this->countriesOwned->size(); ++i) {
            Country* current = countriesOwned->at(i);
            if(current->getTroopCount() > 1){
                validAttackCountries->push_back(current);
            }
            // TODO: check if a country's neighbours are all owned by us
        }

		for (int i = 0; i < validAttackCountries->size(); ++i) {
			cout << i + 1 << " " << validAttackCountries->at(i)->toString() << endl;
		}
        
        cout << "Please selected an option " << "(1 to " << validAttackCountries->size() << "): ";
        
        do {
            cin >> *selectedAttackCountry;
        } while(*selectedAttackCountry < 1 || *selectedAttackCountry > validAttackCountries->size());
        
        cout << " " << endl;
        
        // The attacking country that was chosen and initializing the size of it's neighbours
        attackingCountry = validAttackCountries->at(*selectedAttackCountry-1);
        *sizeOfNeighbours = attackingCountry->getAdjacencyList()->size();
        
        // ----------- SELECTING THE VALID COUNTRY TO DEFEND ------------
        
        cout << "Choose the country you want to attack " << endl;
        
        // For loop that fills up validDefendCountries vector with valid neighbours
        // Printing out the countries that are valid to attack
        for(int i = 0; i < *sizeOfNeighbours; ++i) {

            Country* current = attackingCountry->getAdjacencyList()->at(i);

			// check that we do not own the country || the country is adjacent to the attackingFrom country
            if(current->getOwnerID() != attackingCountry->getOwnerID() || attackingCountry->isCountryAdjacentToMe(current)) {
                validDefendCountries->push_back(current);
            }

            cout << " " << endl;
            // TODO: check if a country's neighbours are all owned by us
        }

		for (int i = 0; i < validDefendCountries->size(); ++i) {
			cout << i + 1 << ": " << validDefendCountries->at(i)->toString() << endl;
		}
        
        cout << "Please selected an option " << "(1 to " << *sizeOfNeighbours << "): ";
        
        
        // Takes in a valid country
        do {
            cin >> *selectedDefendCountry;
        } while(*selectedDefendCountry < 1 || *selectedDefendCountry > validDefendCountries->size());
        
        cout << " " << endl;
        
        // The defending country is chosen
        defendingCountry = validDefendCountries->at(*selectedDefendCountry-1);
        
        /** ----- CALLING THE DICE OBJECT FOR THE ATTACKING AND DEFENDING PLAYER -----*/
        
        // Setting the defending country's player
        defendingPlayer =  static_cast<Player* > (defendingCountry->owner);
        
        // Setting the armies
        
        *attackingArmies = this->getTroopCount(attackingCountry)-1;
        *defendingArmies = defendingPlayer->getTroopCount(defendingCountry);
        
        cout << "Attacking country " <<  *attackingArmies << endl;
        
        // Rolling dice of attacking and defending players respectively
        cout << "Attacking Player's turn to roll dice..." << endl;
        this->diceFacility(attackerRoll, attackingArmies);
        cout << " " << endl;
        cout << "Defending Player's turn to roll dice..." << endl;
        //player->diceFacility(defenderRoll);
        
        // Compares both dice to select winner
        defendingPlayer->diceFacility(defenderRoll, defendingArmies);
        
        this->compareDiceObjects(defendingPlayer, attackingCountry, defendingCountry);
    
        if(this->getTroopCount(attackingCountry) <= 1) {
            cout << "Not enough troops to keep on attacking " << endl;
            break;
        }
        
        if(defendingCountry->getTroopCount() == 0) {
            this->addCountries(defendingCountry);
            
            vector<Country *> * v = defendingPlayer->getCountriesOwned();
            
            int i = 0;
            for(vector<Country*>::iterator it = v->begin(); it != v->end(); ++it){
                if(v->at(i)->equals(defendingCountry) ) {
                    v->erase(it);
                }
                ++i;
            }
            
        }
        
        
        cout << "Do you want to attack further? (yes/no): ";
        cin >> *willAttack;
    }
    
    
    // Delete Pointers
    delete attackerRoll;
    delete defenderRoll;
    delete attackingArmies;
    delete defendingArmies;
    delete selectedDefendCountry;
    delete selectedAttackCountry;
    delete validAttackCountries;
    delete validDefendCountries;
    delete sizeOfNeighbours;
    delete willAttack;
    
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

	} while ((userChoice < 1) || (userChoice > countries->size()));
	return countries->at(userChoice - 1);
}


int Player::selectArmiesToReinforce( Country& source, int remainingArmies) {
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

	if (playerHand->size() > 4) {
		
		while (playerHand->size() > 4) { // to cover the case of killing off other players and getting a ton of cards
			cout << " You have more than 4 cards so you have to exchange " << endl;
			armiesFromExchange = playerHand->exchange();
		}
	}
	else if(playerHand->size() > 2){
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
		std::cout << *name << std::endl;
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


// DICE METHODS
void Player::diceFacility(int* maxRoll, int* numOfArmies) {
    myDice->rollDice(maxRoll, numOfArmies);
}


void Player::compareDiceObjects(Player *player, Country* attackingCountry, Country* defendingCountry) {
    int temp = 0;
    
    while( (temp < 2) & (temp < defendingCountry->getTroopCount())) {
        if(defendingCountry->getTroopCount() == 0) {
            cout << "The defending country has lost all it's countries!!!!" << endl;
            cout << "The defending country now belongs to the attacking country!!!!" << endl;
        }
        else {
            if(this->myDice->container[temp] <= player->myDice->container[temp]) {
               cout << "The attacking player has lost this round and loses one army " << endl;
               // Reducing the number of armies in attacking country
               attackingCountry->setTroopCount(attackingCountry->getTroopCount()-1);
            }
            else {
                cout << "The defending player has lost this round and loses one army " << endl;
                // Reducing the number of armies in defending country
                defendingCountry->setTroopCount(defendingCountry->getTroopCount()-1);
           }
        }
        
        temp++;
    }
}



