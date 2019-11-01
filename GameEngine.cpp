#include "GameEngine.h"

GameEngine::GameEngine(string filePathToMapFolder)
{
	intitializeGame(filePathToMapFolder);
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

	// 1) get info from user (must be done before creating as per assignment)
	string selectedMapPath = getSelectedMapPath();
	selectNumberOfPlayers();
	
	// 2) create and populate game objects (done after as per assignment)
	// there is an order to these methods (makeMap before makeDeck -> need map size in makeDeck)
	makeMap(selectedMapPath);
	makePlayers();
	makeDeck();
}


void GameEngine::makeMap(string filePathToMap) {

	bool isValid = false;

	do {
		// create map
		MapLoader ml(filePathToMap);
		GameEngine::gameMap = ml.init();

		// check if map is valid
		isValid = GameEngine::gameMap->isMapConnected();
		if (!isValid) {
			std::cout << "Error: Map at " << filePathToMap << " is not connected. Please fix map file or try another map file." << std::endl;
			delete GameEngine::gameMap;
		}

		// TODO check with Danny to validate map through the maploader and how to test that (ie. returns NULL???)

	} while (!isValid);


}

void GameEngine::selectNumberOfPlayers() {

	GameEngine::playerCount = new int();

	const int minPlayers = 2; // as defined in Risk rules
	const int maxPlayers = 6; // as defined in Risk rules

	std::cout << "How many players today?" << std::endl;
	do {
		std::cin >> *GameEngine::playerCount;

	} while (*GameEngine::playerCount < minPlayers || *GameEngine::playerCount > maxPlayers);
}

void GameEngine::makePlayers() {

	GameEngine::gamePlayers = new std::vector<Player*>();

	// Create new players and put in vector
	for (int i = 0; i < *GameEngine::playerCount; ++i) {
		GameEngine::gamePlayers->push_back(new Player());
	}

}

void GameEngine::makeDeck() {

	int numCountries = GameEngine::gameMap->countries->size();
	GameEngine::gameDeck = new Deck();
	GameEngine::gameDeck->loadDeck(numCountries);

}

struct path_leaf_string
{
	std::string operator()(const std::filesystem::directory_entry& entry) const
	{
		return entry.path().string();
	}
};

string GameEngine::getSelectedMapPath() {

	stringvec v;
	read_directory(".\\Maps", v);

	// TODO: clean vector of 'dirs' and all files not ending in '.map'

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
		std::cin >> userMapSelection; // TODO: validate input

		if (userMapSelection < 0 || userMapSelection >= v.size()) {
			std::cout << "**Please ensure your number is between 1 and " << v.size() << " -> ";
		}

	} while (userMapSelection < 0 || userMapSelection >= v.size());

	return v.at(userMapSelection);
}

void GameEngine::read_directory(const std::string& name, stringvec& v)
{
	std::filesystem::path p(name);
	std::filesystem::directory_iterator start(p);
	std::filesystem::directory_iterator end;
	std::transform(start, end, std::back_inserter(v), path_leaf_string());

	// TODO: make sure that only files (not dir) are read and only vector thos that end in ".map"
}

void GameEngine::cleanDirectoryVector(stringvec) {

}

Map * GameEngine::getMap() { return GameEngine::gameMap; }

std::vector<Player *> * GameEngine::getPlayers() { return GameEngine::gamePlayers; }

Player * GameEngine::getPlayerAt(int index) { return GameEngine::gamePlayers->at(index); }

Deck * GameEngine::getDeck() { return GameEngine::gameDeck; }

//Player * GameEngine::nextPlayer() {
//
//	return GameEngine::gamePlayers->at(++(*GameEngine::currentPlayer) % *GameEngine::playerCount);
//
//}