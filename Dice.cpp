// Including necessary libraries
#include "Dice.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Constructor
Dice::Dice() {
    
    // Initializes totalRolls
    container = new int[0];
    totalRolls = new int(0);
    
    // Initializes value and valuePercentage
    value = new int[6];
    valuePercentage = new double[6];
    
    for(int i = 0; i < 6; i++) {
        value[i] = 0;
    }
}

Dice::~Dice() {
    
    // Delete pointers
    delete container;
    delete totalRolls;
    delete []value;
    delete []valuePercentage;
    
    // setting pointers to NULL
    container = NULL;
    totalRolls = NULL;
    value = NULL;
    valuePercentage = NULL;
}


// Implementing all the methods
void Dice::rollDice(int* maxRoll, int* numOfArmies) {
    
    int temp;
    
    // Int variable to initialize numOfRolls

    
    // Prompting user for number of dice to roll
    cout << "Roll a dice from 1 and up to ( " << 1 << " & " << *maxRoll << " )" << endl;
    cin >> temp;
    
    while (temp > *maxRoll || temp > *numOfArmies) {
        cout << "Please roll a dice from 1 and upto ( " << 1 << " & " << *maxRoll << " )" << endl;
        cin >> temp;
    }
    
    // Initializing the total roll
    numOfRolls = &temp;
    *totalRolls += *numOfRolls;
    
    // Initializing the container
    container = new int[*numOfRolls];
    
    // For loop that rolls the dice "numOfRolls" times
    for(int i = 0; i < *numOfRolls; i++) {
        container[i] = (rand() % NUM_OF_VALUES) + 1;
    }
    
    // Sorts the container array from highest to lowest
    sortContainer();
    showValues();
    valueTracker();
    percentageTracker();
    showPercentages();
    
    cout << " " << endl;
    
}

// Sorting method
void Dice::sortContainer() {
    
    // Temporary variable to do swapping
    int temp;
    
    // Sorting the container
    for(int i = 0; i < *numOfRolls-1; i++) {
        for (int j = i+1; j < *numOfRolls; j++) {
            
            if(container[i] < container[j]) {
                temp = container[i];
                container[i] = container[j];
                container[j] = temp;
            }
        }
    }
}

// Shows how many times each value was rolled
void Dice::valueTracker() {
    
    // For loop to increment the value that is rolled
    for(int i = 0; i < *numOfRolls; i++) {
        
        switch (container[i])
        {
            case 1:
                value[0] = value[0]+1;
                break;
            case 2: // code to be executed if n = 2;
                value[1] = value[1]+1;
                break;
            case 3:
                value[2] = value[2]+1;
                break;
            case 4: // code to be executed if n = 2;
                value[3] = value[3]+1;
                break;
            case 5:
                value[4] = value[4]+1;
                break;
            case 6:
                value[5] = value[5]+1;
                break;
        }
    }
    
    // For loop that displays number of times each value was rolled
    for(int i = 0; i < NUM_OF_VALUES; i++) {
        cout << i+1;
        cout << " has been rolled ";
        cout << value[i];
        cout << " times " << endl;
    }
    
}

// Tracks the percentage of the values rolled
void Dice::percentageTracker() {
    
    // Calculates the percentage of each value rolled
    for(int i = 0; i < NUM_OF_VALUES; i++) {
        valuePercentage[i] = (value[i] / (double) *totalRolls) * 100;
    }
    
}

// Displays the percentage of each value rolled
void Dice::showPercentages() {
    for(int i = 0; i <NUM_OF_VALUES; i++) {
        cout << "The percentage of ";
        cout << i+1;
        cout << " rolled: ";
        cout << valuePercentage[i] << endl;
    }
}
// Shows the values rolled
void Dice::showValues() {
    for(int i = 0; i < *numOfRolls; i++) {
        cout << "The value are : ";
        cout << container[i] << endl;
    }
}






