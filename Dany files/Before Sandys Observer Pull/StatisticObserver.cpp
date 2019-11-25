#include "StatisticObserver.h"
#include "iostream"
#include "Player.h"

StatisticObserver::StatisticObserver() {
};

StatisticObserver::StatisticObserver(Player* pl) {
	p = pl;
};

StatisticObserver::~StatisticObserver() {
};

void StatisticObserver::Update() {

		printBarGraph();
}

void StatisticObserver::printBarGraph() {

	calculateNewPercentage();

	for (int i = 0; i < dominationPercentage.size(); i++) {
		// Each 4% represents one *
		if (dominationPercentage[i] == 0)
			continue;
		int numberOfStars = (dominationPercentage[i] / 4) + 1;
		std::cout << "Player " << (i + 1) << ": ";
		for (int j = 0; j < numberOfStars; j++)
			std::cout << '*';
		std::cout << " " << dominationPercentage[i] << '%' << std::endl;
	}

}

void StatisticObserver::calculateNewPercentage() {
	double totalCountries = map->countryDictionary->size();

	dominationPercentage.clear();
	for (auto& player : players) {
		// Calculate the percentage owned by every player
		double playerPercentage = player->getCountriesOwned()->size() * 100.0 / totalCountries;
		dominationPercentage.push_back((int)playerPercentage);
	}

}

vector<Player*> StatisticObserver::getPlayers(){
	
	return players;

}

 vector<int> StatisticObserver::getDominationPercentage()  {
	return dominationPercentage;
}


