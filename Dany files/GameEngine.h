 #pragma once

#include "Player.h"
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <vector>
#include <map>
#include <iterator>
#include <random> 

typedef std::vector<std::string> stringvec;


class startUpPhase {
public:
	static void startUp(const Map* map, vector<Player*>* inputVec);
private:

	//vector that contains the player objects
	static vector<Player*>* playerVec;

	//a function that will randomly shuffle (rotate to be more precise) the playerVector while maintaining a circular order
	static void shuffle();

	//a function that takes in a map as a parameter, and distributes it to the players in a rounf robbin fassion
	static void distributeCountries(vector <Country*>* inputMap);

	//assigns armies to every country of every player
	static void assignArmies();

	// to speed up testing
	static void TESTautoAssignTroops();
};


class GameEngine
{

private:
	
	//int * currentPlayer; // index of the current player
	int * playerCount;
	std::vector<Player *> * gamePlayers;
	Map * gameMap;
	Deck * gameDeck;

	int* turnNumber;

	void intitializeGame(string filePathToMapFolder);

	bool makeMap(string filePathToMap);
	void makePlayers();
	void makeDeck();

	void read_directory(const std::string& name, stringvec& v);
	string getSelectedMapPath();
	void selectNumberOfPlayers();
	void cleanDirectoryVector(stringvec* v);

public:

	// constructors:
	GameEngine(string filePathToMapFolder = ".\\Maps");
	~GameEngine();

	// getters and setters:
	Map * getMap();
	std::vector<Player *> * getPlayers();
	Player * getPlayerAt(int index);
	Deck * getDeck();
	void start();

	// game methods:
	//Player * nextPlayer(); // just call this to move to the next player

};

