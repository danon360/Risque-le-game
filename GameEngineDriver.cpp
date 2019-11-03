#include "GameEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <filesystem>



int main() {

	// 1) Validate that invalide maps exit gracefully
	 
	/*
		INSTRUCTION FOR MAKER:
			first choose "UnconnectedMap.map" -> exits gracefully asking you to pick another map;
			then choose "InvalidMap.map" -> exits gracefully asking you to pick another map;
			finally, choose "GoodMap.map" -> enter the number of players and the test will run
	*/
	GameEngine game;

	// 2) The right number of players is created, a deck with the right number of cards is created.

	std::cout << "Printing coutries continents " << std::endl;

	for (int i = 0; i < game.getMap()->countries->size() ; ++i) {

		std::cout << "Owner ID: " << game.getMap()->countries->at(i)->getOwnerID() << std::endl;
	}


	std::cout << "There should be " << game.getPlayers()->size() << " players" << std::endl;
	std::cout << "Printing player names:" << std::endl;
	for (int i = 0; i < game.getPlayers()->size(); ++i) {
		std::cout << "    " << game.getPlayers()->at(i)->getName() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "The size of the deck should be " << game.getMap()->countries->size() << std::endl;
	std::cout << "There are currently " << game.getDeck()->nCards() << " cards in the deck " << std::endl;

	return 0;
} // END OF MAIN()