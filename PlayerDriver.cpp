//#include "Cards.h"
#include "Player.h"
#include "Dice.h"
#include "Map.h"
#include <iostream>
using std::vector;
using namespace std;

// Driver class
int main() {
    // Creating player object
    Player p1;
    Player p2;
    // Hello
    
    // Creating a bunch of countries
<<<<<<< HEAD
    Country * country_a = new Country("country_a", 2,2,2);
    Country * country_b = new Country("country_b", 2,2,1);
    Country * country_c = new Country("country_c", 2,2,2);
    Country * country_d = new Country("country_d", 2,2,2);
    Country * country_e = new Country("country_e", 2,2,2);
    Country * country_f = new Country("country_f", 2,2,2);
=======
    Country * country_a = new Country("country_a", 1, 1, 1);
    Country * country_b = new Country("country_b", 2, 1, 1);
    Country * country_c = new Country("country_c", 3, 1, 1);
    Country * country_d = new Country("country_d", 4, 1, 1);
    Country * country_e = new Country("country_e", 5, 1, 1);
    Country * country_f = new Country("country_f", 6, 1, 1);
>>>>>>> 1ebe668530aafe099d249082006ce5a28b80ea49
    
    // Adding the countries to my vector
    p1.addCountries(country_a);
    p1.addCountries(country_b);
    p1.addCountries(country_c);
    p1.addCountries(country_d);
    p1.addCountries(country_e);
    p1.addCountries(country_f);
    
    // Player-1
    p1.collectionOfCountries();
    p1.diceObject();
    
    // Player-2
    p2.collectionOfCountries();
    p2.diceObject();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
     Card * card1 = new Card(INFANTRY);
     Card * card2 = new Card(CAVALRY);
     Card * card3 = new Card(ARTILLERY);
     Card * card4 = new Card(ARTILLERY);
     Card * card5 = new Card(INFANTRY);
    
     p1.addCards(card1);
     p1.addCards(card2);
     p1.addCards(card3);
     p1.addCards(card4);
     p1.addCards(card5);
     
     p1.collectionOfRiskCards();
     */
    cout << "Done" << endl;
}


