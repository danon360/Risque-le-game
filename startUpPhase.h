#pragma once
#include "Player.h"
#include <random>
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
	
};
