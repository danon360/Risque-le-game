#include "GameEngine.h"


GameEngine::GameEngine(string filePathToMapFolder = ".\\Maps")
{
	intitializeGame(filePathToMapFolder);
}


GameEngine::~GameEngine()
{
	delete GameEngine::playerCount;
	GameEngine::playerCount = nullptr;

	for (int i = 0; i < GameEngine::gamePlayers->size(); ++i)
		delete GameEngine::gamePlayers->at(i);
	delete[] GameEngine::gamePlayers;
	GameEngine::gamePlayers->clear();
	GameEngine::gamePlayers = nullptr;

	delete GameEngine::gameMap;
	GameEngine::gameMap = nullptr;

	delete GameEngine::deck;
	deck = nullptr;
}


void GameEngine::intitializeGame(string filePathToMapFolder) {

	// 1) get info from user (must be done before creating as per assignment)
	selectNumberOfPlayers();
	string selectedMapPath = getSelectedMapPath();
	
	// 2) create and populate game objects (done after as per assignment)
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
			std::cout << "Error: Map is not connected. Please fix map file or try another map." << std::endl;
			delete GameEngine::gameMap;
		}
	} while (!isValid);


}

void GameEngine::selectNumberOfPlayers() {

	GameEngine::playerCount = new int();

	const int minPlayers = 2; // as defined in Risk rules
	const int maxPlayers = 6; // as defined in Risk rules

	std::cout << "How many players today?" << std::endl;
	do {
		std::cin >> *GameEngine::playerCount;

	} while (*GameEngine::playerCount < 2 || *GameEngine::playerCount > 6);
	(*GameEngine::playerCount)--; // subtract 1 to make it an indexable number for vector
}

void GameEngine::makePlayers() {

	// Create new players and put in vector
	for (int i = 0; i < *GameEngine::playerCount; ++i) {
		GameEngine::gamePlayers->push_back(new Player());
	}

}

void GameEngine::makeDeck() {

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

	if (v.empty()) {
		std::cout << "Error: no map included in specified directory" << std::endl;
		std::cout << "Exiting game - please add a *.map file in Maps directory and restart the game... Goodbye friend" << std::endl;
	}

	int userMapSelection;
	do {
		std::cout << "Select a map:" << std::endl;

		for (int i = 0; i < v.size(); ++i) {
			std::cout << i + 1 << ": " << v.at(i) << std::endl;
		}
		std::cin >> userMapSelection;
		userMapSelection--;

	} while (userMapSelection < 0 || userMapSelection >= v.size());

	return v.at(userMapSelection);
}

void GameEngine::read_directory(const std::string& name, stringvec& v)
{
	std::filesystem::path p(name);
	std::filesystem::directory_iterator start(p);
	std::filesystem::directory_iterator end;
	std::transform(start, end, std::back_inserter(v), path_leaf_string());
}
