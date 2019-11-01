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
	
	//int * currentPlayer; // index of the current player
	int * playerCount;
	std::vector<Player *> * gamePlayers;
	Map * gameMap;
	Deck * gameDeck;

	void intitializeGame(string filePathToMapFolder);

	void makeMap(string filePathToMap);
	void makePlayers();
	void makeDeck();

	void read_directory(const std::string& name, stringvec& v);
	string getSelectedMapPath();
	void selectNumberOfPlayers();
	void cleanDirectoryVector(stringvec vec);

public:

	// constructors:
	GameEngine(string filePathToMapFolder = ".\\Maps");
	~GameEngine();

	// getters and setters:
	Map * getMap();
	std::vector<Player *> * getPlayers();
	Player * getPlayerAt(int index);
	Deck * getDeck();

	// game methods:
	//Player * nextPlayer(); // just call this to move to the next player

};

