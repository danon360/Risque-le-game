#pragma once
#include "Observer.hpp"
#include "Player.h"
#include "Subject.hpp"

class StatisticObserver: public Observer
{

private:
	Player* player;
	Map* map;

	std::vector<Player*> players;
	std::vector<int> dominationPercentage;



public:
	~StatisticObserver();
	StatisticObserver();
	StatisticObserver(Player* pl);


	void Update();

	void printBarGraph();

	vector<int> getDominationPercentage();

	void calculateNewPercentage();

	 vector<Player*> getPlayers();


};

