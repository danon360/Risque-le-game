// Including necessary libraries
#include "Dice.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Implementing all the methods
void Dice::rollDice(int numOfRolls) {
    
    totalRolls = totalRolls+numOfRolls; // Incrementing the total number of dice rolled for this player
    container = new int[numOfRolls]; // Initializing the container
    
    // For loop that rolls the dice "numOfRolls" times
    for(int i = 0; i < numOfRolls; i++) {
        container[i] = (rand() % 6) + 1;
    }
    
    sortContainer(numOfRolls); // Sorts the container array
    showValues(); // Displays the values
    percentageTracker(numOfRolls);
    
    // Deleting the pointer container
    delete[] container;
    container = NULL;
    
}

// Sorting method
void Dice::sortContainer(int numOfRolls) {
    int temp; // Temporary variable
    
    // Sorting the container
    for(int i = 0; i < numOfRolls-1; i++) {
        for (int j = i+1; j < numOfRolls; j++) {
            
            if(container[i] < container[j]) {
                temp = container[i];
                container[i] = container[j];
                container[j] = temp;
                
            }
        }
    }
}

void Dice::percentageTracker(int numOfRolls) {
    
    for(int i = 0; i < numOfRolls; i++) {
        
    switch (container[i])
    {
        case 1:
            trackPercentage[0] = trackPercentage[0]+1;
            break;
        case 2: // code to be executed if n = 2;
            trackPercentage[1] = trackPercentage[1]+1;
            break;
        case 3:
            trackPercentage[2] = trackPercentage[2]+1;
            break;
        case 4: // code to be executed if n = 2;
            trackPercentage[3] = trackPercentage[3]+1;
            break;
        case 5:
            trackPercentage[4] = trackPercentage[4]+1;
            break;
        case 6:
            trackPercentage[5] = trackPercentage[5]+1;
            break;
            
       
      }
    }
    
    for(int i = 0; i < 6; i++) {
        cout << i+1;
        cout << " has been rolled ";
        cout << trackPercentage[i];
        cout << "times " << endl;
    }
    
}

// Show Container Method
void Dice::showValues() {
    for(int i = 0; i < 3; i++) {
        cout << "The value are : ";
        cout << container[i] << endl;
    }
}



// void Dice::valueTracker(int* temp[]) { }
// void Dice::percentageTracker(int* temp[]) { }
// Variables
// rollDice method
// valueTacker method
// percentageTracker method
   
