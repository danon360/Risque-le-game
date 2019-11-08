#include "startUpPhase.h"

//initialising playerVec vector
vector<Player*>* startUpPhase::playerVec = new vector<Player*>();


void startUpPhase::shuffle(){
	srand(time(0));

	//randomly finding the starting player
	int index = rand()%playerVec->size();
	
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
			cout <<"\n "<< currentPlayer->getName() << " : Please provide the number of the country you wish to add an army to (Remaining armies : " << troopCount->at((i) % troopCount->size()) << " )" << endl;
			std::cin >> *countryID;

			//in case the user provides invalid input
			while (std::cin.fail())
			{
				std::cout << "Invalid input"<<"\n "<< currentPlayer->getName() << " : Please provide the number of the country you wish to add an army to(Remaining armies : " << troopCount->at((i) % troopCount->size()) << ")" << endl;
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
					do{
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
					}while (*repeat);

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
void startUpPhase::startUp(const Map* map, vector<Player*>* inputVec) {
	startUpPhase::playerVec = inputVec;
	shuffle();
	distributeCountries(map->countries);
	assignArmies();
}
