//
//  PhaseObserver.cpp
//  Assignment3
//
//  Created by mushfiqur anik on 2019-11-16.
//  Copyright © 2019 mushfiqur anik. All rights reserved.
//

//Phase Observer
#pragma once
#include "PhaseObserver.hpp"
#include "Player.h"
#include <iostream>
using namespace std;

PhaseObserver::PhaseObserver() {
};

PhaseObserver::PhaseObserver(Player* p) {
    currentPlayer = p;
    currentPlayer->Attach(this);
};

PhaseObserver::~PhaseObserver() {
   currentPlayer->Detach(this);
};

void PhaseObserver::Update(int playerID, string phase, string action) {
    //Called by Notify() when state of Subject changes
    Display(playerID, phase, action);
};

void PhaseObserver::Display(int playerID, string phase, string action) {
    // Display the things
    cout << "------------------------OBSERVER PATTERN--------------------------" << endl;
    cout << "| Player : " << playerID << " is " << phase << " " << action << "|" << endl;
    cout << "------------------------------------------------------------------" << endl;
};
