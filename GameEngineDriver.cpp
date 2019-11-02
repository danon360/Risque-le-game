#include "GameEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <filesystem>



int main() {

	// 1) Validate that invalide maps exit gracefully
	GameEngine unconnectedMapGame; // "choose UnconnectedMap.map"
	GameEngine invalidMapGame; // "choose InvalidMap.map"
	GameEngine goodMapGame; // choose "GoodMap.map"

	// 2) The right number of players is created, a deck with the right number of cards is created.

	std::cout << "There should be " << goodMapGame.getPlayers()->size() << " players" << std::endl;
	std::cout << "Printing player names:" << std::endl;
	for (int i = 0; i < goodMapGame.getPlayers()->size(); ++i) {
		std::cout << "    Country " << i+1 << ": " << goodMapGame.getPlayers()->at(i)->getName() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "The size of the deck should be " << goodMapGame.getMap()->countries->size() << std::endl;
	std::cout << "There are currently " << goodMapGame.getDeck()->nCards() << " cards in the deck " << std::endl;

	return 0;
} // END OF MAIN()