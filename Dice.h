#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

// Start of class Dice
class Dice {
    
// Public methods
public:
    // Variables
    int totalRolls = 0;
    int* container;
    int trackPercentage [6] = {0,0,0,0,0,0};
  
    
    // Methods
    void rollDice(int numOfRolls);
    void percentageTracker(int numOfRolls);
    void sortContainer(int numOfRolls);
    void showValues();
    
    /*
    void sortContainer(int* container[]);
    void valueTracker(int* temp[]);
    void percentageTracker(int* temp[]);*/
};
