#include "GameEngine.h"

GameEngine::GameEngine(string filePathToMapFolder)
{
	turnNumber = new int(1);

	intitializeGame(filePathToMapFolder);
	startUpPhase::startUp(gameMap, gamePlayers);
}

GameEngine::~GameEngine()
{
	//delete GameEngine::currentPlayer;
	//GameEngine::currentPlayer = nullptr;

	delete GameEngine::playerCount;
	GameEngine::playerCount = nullptr;

	for (int i = 0; i < GameEngine::gamePlayers->size(); ++i)
		delete GameEngine::gamePlayers->at(i);
	delete GameEngine::gamePlayers;
	GameEngine::gamePlayers = nullptr;

	delete GameEngine::gameMap;
	GameEngine::gameMap = nullptr;

	delete GameEngine::gameDeck;
	gameDeck = nullptr;
}


void GameEngine::intitializeGame(string filePathToMapFolder) {

	string selectedMapPath;
	bool isValidMap = false;

	do {

		selectedMapPath = getSelectedMapPath();
		isValidMap = makeMap(selectedMapPath);

	} while (!isValidMap);

	selectNumberOfPlayers();
	makePlayers();
	makeDeck();
}


bool GameEngine::makeMap(string filePathToMap) {

	bool isValid = false;

	do {
		// create map
		try {
			MapLoaderAdapter ml(filePathToMap);
			GameEngine::gameMap = ml.init();

			// check if map is valid
			isValid = GameEngine::gameMap->isMapConnected();
			if (!isValid) {
				std::cout << "Error: Map at " << filePathToMap << " is not connected. Please fix map file or try another map file." << std::endl;
				delete GameEngine::gameMap;
				return false;
			}
		}
		catch (std::exception & e) {
			std::cout << "Problem reading map file, please fix file or try another one." << std::endl;
			return false;
		}

	} while (!isValid);

	return true;
}

void GameEngine::selectNumberOfPlayers() {

	GameEngine::playerCount = new int();

	const int minPlayers = 2; // as defined in Risk rules
	const int maxPlayers = 6; // as defined in Risk rules

	std::cout << "How many players today?" << std::endl;
	do {

		std::cout << std::endl << ">>> ";
		std::cin >> *GameEngine::playerCount;
		while (std::cin.fail())
		{
			std::cout << "Invalid Entry\nEnter a number between 2 and 6" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> *GameEngine::playerCount;
		}
		std::cout << std::endl;

	} while (*GameEngine::playerCount < minPlayers || *GameEngine::playerCount > maxPlayers);
}

void GameEngine::makePlayers() {

	GameEngine::gamePlayers = new std::vector<Player*>();

	std::string name;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip endline from previous 'cin'

	// Create new players and put in vector
	for (int i = 0; i < *GameEngine::playerCount; ++i) {

		std::cout << "Please enter player " << i+1 << "'s name: ";
		std::getline(std::cin, name);
		std::cout << std::endl;
		gamePlayers->push_back(new Player(new string(name), i+1, gameMap)); // set name and unique ID and give it gameMap

		// set the strategy of each player
		std::cout << "What type of player is " << name << " going to be?" << std::endl;
		std::cout << "\t1. Human" << std::endl;
		std::cout << "\t2. Aggressive Bot" << std::endl;
		std::cout << "\t3. Benevolent Bot" << std::endl;
		int playerTypeChoice;
		do {
			std::cin >> playerTypeChoice;
			switch (playerTypeChoice) {
			case 1:
				gamePlayers->at(i)->setStrategy(new HumanStrategy());
				break;
			case 2:
				gamePlayers->at(i)->setStrategy(new AgressiveStrategy());
				break;
			case 3:
				gamePlayers->at(i)->setStrategy(new BenevolentStrategy());
				break;
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} while (playerTypeChoice < 1 || playerTypeChoice > 3);
		std::cout << std::endl;

	}
	std::cout << std::endl;

}

void GameEngine::makeDeck() {

	int numCountries = GameEngine::gameMap->countries->size();
	GameEngine::gameDeck = new Deck();
	GameEngine::gameDeck->loadDeck(numCountries);

}

struct path_leaf_string
{
	std::string operator()(const std::experimental::filesystem::directory_entry& entry) const
	{
		return entry.path().string();
	}
};

string GameEngine::getSelectedMapPath() {

	stringvec v;
	read_directory(".\\Maps", v);

	cleanDirectoryVector(&v);

	if (v.empty()) {
		std::cerr << "Error: no map included in specified directory" << std::endl;
		std::cerr << "Exiting game - please add a *.map file in Maps directory and restart the game... Goodbye friend" << std::endl;
		exit(1);
	}

	int userMapSelection;
	do {
		std::cout << "Select a map:" << std::endl;

		for (int i = 0; i < v.size(); ++i) {
			std::cout << i + 1 << ": " << v.at(i) << std::endl;
		}

		std::cout << std::endl << ">>> ";
		std::cin >> userMapSelection;
		while (std::cin.fail())
		{
			std::cout << "Invalid Entry\nEnter a numberic in range show above" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> userMapSelection;
		}
		std::cout << std::endl;

		if (userMapSelection < 1 || userMapSelection > v.size()) {
			std::cout << "**Please ensure your number is between 1 and " << v.size() << " -> ";
		}

	} while (userMapSelection < 1 || userMapSelection > v.size());

	return v.at(userMapSelection - 1);
}

void GameEngine::read_directory(const std::string& name, stringvec& v)
{
	std::experimental::filesystem::path p(name);
	std::experimental::filesystem::directory_iterator start(p);
	std::experimental::filesystem::directory_iterator end;
	std::transform(start, end, std::back_inserter(v), path_leaf_string());
}

// removes all entries that do not end in ".maps"
void GameEngine::cleanDirectoryVector(stringvec* v) {

	v->erase(std::remove_if(v->begin(), v->end(), [](string str) {
		const string mapSuffix = ".map";
		return !(str.substr(str.size() - 4, str.size()).compare(mapSuffix) == 0);
		}),
		v->end()
			);
}

Map* GameEngine::getMap() { return GameEngine::gameMap; }

std::vector<Player*>* GameEngine::getPlayers() { return GameEngine::gamePlayers; }

Player* GameEngine::getPlayerAt(int index) { return GameEngine::gamePlayers->at(index); }

Deck* GameEngine::getDeck() { return GameEngine::gameDeck; }


void GameEngine::start() {

	bool done = false;
	Player* currentPlayer;
	string* ansswer = new string();

	while (!done) {

		std::cout << "**********************************************************************************" << std::endl;
		std::cout << "**********************************************************************************" << std::endl;
		std::cout << "                                 Turn: " << *turnNumber << std::endl;
		std::cout << "**********************************************************************************" << std::endl;
		std::cout << "**********************************************************************************" << std::endl;
		std::cout << std::endl;

		for (int i = 0; i < gamePlayers->size(); i++) {

			currentPlayer = gamePlayers->at(i);

			currentPlayer->reinforce();
			currentPlayer->attack();
			done = checkVictory(); // breaks out of loop
			if (done)
				break;
			currentPlayer->fortify();

			// if player has conquered at least 1 country, he draws a card
			if (currentPlayer->getHasConqueredThisTurn()) {
				std::cout << currentPlayer->getName() << " has been given a card for having conquered a country this turn" << std::endl;
				currentPlayer->getHand()->add(gameDeck->draw());
				currentPlayer->resetHasConqueredThisTurn();
			}
		}

		++*turnNumber;
	}

	

}

bool GameEngine::checkVictory() {

	// end game condition: if n-1 players have no countries;

	const int playerCount = gamePlayers->size();
	int playersWithNoCountries = 0;

	Player* winner = gamePlayers->at(0); // initialized to calm compiler
	Country* current;
	Player* currentPlayer;
	// check every player for having 0 countries
	for (int i = 0; i < playerCount; ++i) {
		currentPlayer = gamePlayers->at(i);

		if (currentPlayer->getCountriesOwned()->size() == 0) // player has no countries
			++playersWithNoCountries;
		else
			winner = currentPlayer;
	}

	if (playersWithNoCountries == playerCount - 1) { // there is only 1 player left with any countries
		std::cout << "**********************************************************************************" << std::endl;
		std::cout << "**********************************************************************************" << std::endl;
		std::cout << "     Congratulations " << winner->getName() << " !!!. You won the game!!" << std::endl;
		std::cout << "**********************************************************************************" << std::endl;
		std::cout << "**********************************************************************************" << std::endl;
		return true;
	}
	
	return false;
}

//initialising playerVec vector
vector<Player*>* startUpPhase::playerVec = new vector<Player*>();


void startUpPhase::shuffle() {
	srand(time(0));

	//randomly finding the starting player
	int index = rand() % playerVec->size();

	//rotating the vecor. The "playerVec->begin() + index" iterator will now be the start iterator, 
	//and everything that was before it in the factor will now be at the end of the vector
	std::rotate(playerVec->begin(), playerVec->begin() + index, playerVec->end());
}

void startUpPhase::distributeCountries(vector<Country*>* inputVec) {

	//shuffling the vector of countries to acheive randomness
	auto rng = std::default_random_engine(time(NULL));
	std::shuffle(inputVec->begin(), inputVec->end(), rng);

	//NOTE : THIS ONLY WORKS ON LATEST VERSION
	//std::random_shuffle(countryMap->begin(), countryMap->end());

	//distributing the shuffled countries to th eplayers in a rounf robbin fashion
	for (int i = 0; i < inputVec->size(); i++) {
		startUpPhase::playerVec->at((i) % startUpPhase::playerVec->size())->addCountries(inputVec->at(int(i)));


		inputVec->at(i)->owner = playerVec->at((i) % startUpPhase::playerVec->size());
		//cout << (static_cast<Player*>(inputVec->at(i)->owner))->getName() << endl;
	}
}
void startUpPhase::assignArmies() {
	//variable to keep track of the number of armies each player should be given
	int* numOfArmies = new int();
	//variable to keep track of the current player
	Player* currentPlayer;
	//variable to keep track of the countries owned by the current player
	vector<Country*>* currentCountries;
	int* countryID = new int();

	vector<int>* countriesRecord = new vector<int>(playerVec->size());

	vector<int>* troopCount = new vector<int>(playerVec->size());

	//vector to keep track of which players have 
	//vector<bool>* warning = new vector<bool>(playerVec->size());
	bool* warning = new bool(false);
	//boolean variable 
	bool* repeat = new bool(false);

	//determining the number of armies each player gets 
	switch (startUpPhase::playerVec->size()) {

	case 1:
		std::cerr << "Invalid number of players. The game will now exit" << endl;
		break;
	case 2:
		*numOfArmies = 40;
		break;
	case 3:
		*numOfArmies = 35;
		break;
	case 4:
		*numOfArmies = 30;
		break;
	case 5:
		*numOfArmies = 25;
		break;
	case 6:
		*numOfArmies = 20;
		break;
	default:
		std::cerr << "Invalid number of players. The game will now exit" << endl;
		exit(1);
		break;
	}

	//filling the vector to keep track of how many unassigned countries ,and how many troops, a player still has
	for (int j = 0; j < playerVec->size(); j++) {
		countriesRecord->at(j) = playerVec->at(j)->getCountriesOwned()->size();
		troopCount->at(j) = *numOfArmies;
	}

	for (int i = 0; i < (*numOfArmies * startUpPhase::playerVec->size()); i++) {

		//variable to keep track of the current player
		currentPlayer = startUpPhase::playerVec->at((i) % startUpPhase::playerVec->size());

		//variable to keep track of the list of countries the current player owns
		currentCountries = currentPlayer->getCountriesOwned();

		//if the number of remaining troops = number of unassigned countries, we should allow assigning troops only to unassigned countries
		if (troopCount->at((i) % troopCount->size()) <= countriesRecord->at((i) % countriesRecord->size())) {
			//warning->at((i) % troopCount->size()) = true;
			*warning = true;
		}
		do {
			cout << currentPlayer->getName() << " owns the following countries : " << endl;
			for (int j = 0; j < currentCountries->size(); j++) {
				cout << " country number : " << j + 1 << " , Name: " << currentCountries->at(j)->getName() << " Troop count : " << currentCountries->at(j)->getTroopCount() << endl;
			}
			cout << "\n " << currentPlayer->getName() << " : Please provide the number of the country you wish to add an army to (Remaining armies : " << troopCount->at((i) % troopCount->size()) << " )" << endl;
			std::cin >> *countryID;

			//in case the user provides invalid input
			while (std::cin.fail())
			{
				std::cout << "Invalid input" << "\n " << currentPlayer->getName() << " : Please provide the number of the country you wish to add an army to(Remaining armies : " << troopCount->at((i) % troopCount->size()) << ")" << endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> *countryID;
			}

			if (*countryID < 1 || *countryID > currentCountries->size()) {
				cout << " Invalid number." << endl;
				*repeat = true;
			}
			else {
				*repeat = false;
			}
		} while (*repeat);

		//making sure repeat is set to false
		*repeat = false;

		//if the number of remaining unassigned countries = number of remaining troops, we have to take recautions
		if (/*warning->at((i) % warning->size())*/ *warning) {
			do {
				//checking if the player chose a country that has already been assigned armies to
				if (currentCountries->at(*countryID - 1)->getTroopCount() > 0) {
					cout << " you only have " << troopCount->at((i) % troopCount->size()) << " armies left,which have to be assigned to the remaining " << countriesRecord->at((i) % troopCount->size()) << " countries with no troops."
						<< " Please select a country with no armies." << endl;

					//a loop is placed here in case the player provides an invalid number for the country
					do {
						//printing the list of countries again
						for (int j = 0; j < currentCountries->size(); j++) {
							cout << " country number : " << j + 1 << " , Name: " << currentCountries->at(j)->getName() << " Troop count : " << currentCountries->at(j)->getTroopCount() << endl;
						}

						//prompting for input again 
						cout << "\n " << currentPlayer->getName() << " : Please provide the number of the country you wish to add an army to (Remaining armies : " << troopCount->at((i) % troopCount->size()) << " )" << endl;
						std::cin >> *countryID;

						//in case the user proviedes an invalid input
						while (std::cin.fail())
						{
							std::cout << "Invalid input" << "\n " << currentPlayer->getName() << " : Please provide the number of the country you wish to add an army to(Remaining armies : " << troopCount->at((i) % troopCount->size()) << ")" << endl;
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cin >> *countryID;
						}

						//checking if the given value is withing the correct range
						if (*countryID < 1 || *countryID > currentCountries->size()) {
							cout << " Invalid number." << endl;
							*repeat = true;
						}
						else {		//if the value provided is within the correct range, make sure we dont repeat the innermost loop
							*repeat = false;
						}
					} while (*repeat);

					//making sure the we go through the loop and verify everything again.
					*repeat = true;
				}
				else {		//if the player chose a country with no armies assigned to it
					countriesRecord->at((i) % countriesRecord->size())--;
					troopCount->at((i) % troopCount->size())--;
					currentCountries->at(*countryID - 1)->addToTroopCount(1);
					*repeat = false;
				}

			} while (*repeat);
		}
		else {
			//if the country had not been assigned a troop yet decreement no' of available troops and no' of unassigned countries, else only decreement no' of armies
			if (currentCountries->at(*countryID - 1)->getTroopCount() == 0) {
				countriesRecord->at((i) % countriesRecord->size())--;
				troopCount->at((i) % troopCount->size())--;
				currentCountries->at(*countryID - 1)->addToTroopCount(1);
			}
			else {
				troopCount->at((i) % troopCount->size())--;
				currentCountries->at(*countryID - 1)->addToTroopCount(1);
			}
		}

		*warning = false;
	}
	//deleting pointers
	delete repeat;
	delete countryID;
	delete countriesRecord;
	delete troopCount;
	delete warning;
	cout << "Thank you. The game will start shortly.\n";
}
void startUpPhase::TESTautoAssignTroops() {

	int playerCount = 2; // test method only works for 2 players -> change for n players

	

	Player* player1 = playerVec->at(0);
	player1->getCountriesOwned()->at(0)->setOwnerID(*player1->getID());
	player1->getCountriesOwned()->at(0)->setTroopCount(10);
	player1->getCountriesOwned()->at(1)->setOwnerID(*player1->getID());
	player1->getCountriesOwned()->at(1)->setTroopCount(2);

	Player* player2 = playerVec->at(1);
	player2->getCountriesOwned()->at(0)->setOwnerID(*player2->getID());
	player2->getCountriesOwned()->at(0)->setTroopCount(10);
	player2->getCountriesOwned()->at(1)->setOwnerID(*player2->getID());
	player2->getCountriesOwned()->at(1)->setTroopCount(2);

	/*
	for (int i = 0; i < playerVec->size(); i++) {

		Player* currentPlayer = playerVec->at(i);

		for (int j = 0; j < currentPlayer->getCountriesOwned()->size(); j++) {

			Country* currentCountry = currentPlayer->getCountriesOwned()->at(j);

			currentCountry->setTroopCount((rand() % 10) + 1); // set troop count to a rand number between 1 and 10

			if (i % playerCount == 0) {
				currentCountry->setOwnerID(*(currentPlayer->getID())); // set ID to current player's
				currentCountry->owner = currentPlayer; // set the country's owner
			}

		}
	}
	*/
}
void startUpPhase::startUp(const Map* map, vector<Player*>* inputVec) {
	startUpPhase::playerVec = inputVec;
	shuffle();
	distributeCountries(map->countries);
	//assignArmies();
	TESTautoAssignTroops();
}


int main() {

	GameEngine G1(".\\Maps");
	G1.start();
	
}