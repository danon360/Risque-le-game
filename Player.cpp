#include "Player.h"

using namespace std;
using std::vector;

// Default Constructor
Player::Player() {
	countriesOwned = new vector<Country*>;
	//playerHand = new Hand;
	name = new string();
	myDice = new Dice();
    myCountry = new Country();
}

Player::Player(string * _name, int id, Map* map) {
    countriesOwned = new vector<Country*>;
    myCountry = new Country();
	//playerHand = new Hand;
	name = _name;
	myDice = new Dice();
	gameMap = map;
}

/*
Player::Player(vector<Country*>* playerCountries, Dice* playerDice, Hand* hand, string* playerName) {
	countriesOwned = playerCountries;
	myDice = playerDice;
	//playerHand = hand;
	name = playerName;

}*/


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
    vector<Country *> *validAttackCountries;
    vector<Country *> *validDefendCountries;
    
    // Prompts the user for attack
    cout << "Do you want to attack? (yes/no): ";
    cin >> *willAttack;
    
    // Main attack loop
    while (*willAttack == "yes") {
        cout << "Attacking..." << endl;;
        
        /** ----- SELECTING COUNTRIES TO ATTACK FROM AND THE DEFENDING COUNTRY -----*/
        // ----- SELECTING THE VALID COUNTRY TO ATTACK FROM -----
        
        // Setting the size of the valid attacking countries
        validAttackCountries = new vector<Country *>;
        
        cout << "These are the countries that you can attack: " << endl;
        
        // Initializing all the valid attacking countries and display them
        for(int i = 0; i < this->countriesOwned->size(); ++i) {
            Country* current = countriesOwned->at(i);
            if(current->getTroopCount() > 1){
                validAttackCountries->push_back(current);
                cout << i+1 << " " << validAttackCountries->at(i)->toString() << endl;;
            }
            // TODO: check if a country's neighbours are all owned by us
        }
        
        cout << "Please selected an option " << "(1 to " << this->countriesOwned->size() << "): ";
        
        do {
            cin >> *selectedAttackCountry;
        } while(*selectedAttackCountry < 1 || *selectedAttackCountry > validAttackCountries->size());
        
        cout << " " << endl;
        
        // The attacking country that was chosen and initializing the size of it's neighbours
        attackingCountry = validAttackCountries->at(*selectedAttackCountry-1);
        *sizeOfNeighbours = attackingCountry->getAdjacencyList()->size();
        
        // ----------- SELECTING THE VALID COUNTRY TO DEFEND ------------
        
        // Vector that that contains valid neighbours (Neighbours not owned by attackingCountry)
        validDefendCountries = new vector<Country *>;
        
        cout << "Choose the country you want to attack " << endl;;
        
        // For loop that fills up validDefendCountries vector with valid neighbours
        // Printing out the countries that are valid to attack
        for(int i = 0; i < *sizeOfNeighbours; ++i) {
            Country* current = attackingCountry->getAdjacencyList()->at(i);
            
            if(current->getOwnerID() != attackingCountry->getOwnerID()) {
                validDefendCountries->push_back(current);
                cout << i+1 << " " << validDefendCountries->at(i)->toString();
            }
            
            cout << " " << endl;
            // TODO: check if a country's neighbours are all owned by us
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
    
    // Set to null
    attackerRoll = NULL;
    defenderRoll = NULL;
    attackingArmies = NULL;
    defendingArmies = NULL;
    selectedDefendCountry = NULL;
    selectedAttackCountry = NULL;
    validAttackCountries = NULL;
    validDefendCountries = NULL;
    sizeOfNeighbours = NULL;
    willAttack = NULL;
}

void Player::setTroopCount(int troop, Country* country) {
    country->setTroopCount(troop);
}

int Player::getTroopCount(Country* country) {
    return country->getTroopCount();
}



/*

Hand* Player::getHand() {
	return playerHand;
}
*/

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

	vector<int> continentCounter();

	return 0; // DELETE THIS LINE - ADDED SO THAT PROGRAM COMPILES

}

/*
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
  
*/

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






