//
//  PhaseObserver.hpp
//  Assignment3
//
//  Created by mushfiqur anik on 2019-11-16.
//  Copyright © 2019 mushfiqur anik. All rights reserved.
//

#pragma once
#include "Observer.hpp"
#include "Player.h"

class PhaseObserver : public Observer {
public:
    PhaseObserver();
    PhaseObserver(Player* currentPlayer);
    ~PhaseObserver();
	void Update() {};
    void Update(int playerID, string phase, string action);
    void Display(int playerID, string phase, string action);
private:
    Player *currentPlayer;
};
