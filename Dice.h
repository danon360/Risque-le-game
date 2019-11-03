#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

// Start of class Dice
class Dice {
    
// Public methods
public:
    // Variables
    const int NUM_OF_VALUES = 6;
    int* maxRoll;
    int* numOfRolls;
    int* totalRolls;
    int* container;
    int* value;
    double* valuePercentage;
    
    // Constructor and Destructor
    Dice();
    ~Dice();
    
    // Methods
    void compareDiceRolls(Dice* newDice);
	void rollDice(int* maxRoll);
    void sortContainer();
    void valueTracker();
    void percentageTracker();
    void showValues();
    void showPercentages();
  
};
