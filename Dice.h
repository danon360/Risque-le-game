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
    int* numOfRolls;
    int* totalRolls;
    int* container;
    int* value;
    double* valuePercentage;
    
    // Constructor and Destructor
    Dice();
    ~Dice();
    
    // Methods
    void rollDice();
    void sortContainer();
    void valueTracker();
    void percentageTracker();
    void showValues();
    void showPercentages();
  
};
