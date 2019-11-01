#pragma once

#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Dice.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <vector>
#include <map>
#include <iterator>

typedef std::vector<std::string> stringvec;

class GameEngine
{

private:
	
	int * playerCount;
	std::vector<Player *> * gamePlayers;
	Map * gameMap;
	Deck * deck;

	void intitializeGame(string filePathToMapFolder);

	void makeMap(string filePathToMap);
	void makePlayers();
	void makeDeck();

	void read_directory(const std::string& name, stringvec& v);
	string getSelectedMapPath();
	void selectNumberOfPlayers();
	
public:

	GameEngine(string filePathToMapFolder = ".\\Maps");
	~GameEngine();
};

