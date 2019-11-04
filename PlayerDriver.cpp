#include "Cards.h"
#include "Player.h"
#include "Dice.h"
#include "Map.h"
#include <iostream>
using std::vector;
using namespace std;

// Driver class
int main() {
    
    srand(time(0)); // Seed for generating randomn values
    
    // Creating player object
    Player* p1 = new Player();
    Player* p2 = new Player();
    Player* p3 = new Player();

    // Creating bunch of countries
    Country * country_a = new Country("country_a", 1,2,1);
    Country * country_b = new Country("country_b", 2,2,2);
    Country * country_c = new Country("country_c", 3,2,1);
    Country * country_d = new Country("country_d", 4,2,2);
    Country * country_e = new Country("country_e", 5,2,1);
    Country * country_f = new Country("country_f", 6,2,2);
    
    // Setting the country owners
    country_a->owner = p1;
    country_b->owner = p2;
    country_c->owner = p1;
    country_d->owner = p2;
    country_e->owner = p1;
    country_f->owner = p2;
   
    //Adding the countries to my vector
    p1->addCountries(country_a);
    p1->addCountries(country_c);
    p1->addCountries(country_e);
    
    p2->addCountries(country_b);
    p2->addCountries(country_d);
    p3->addCountries(country_f);
    
    // Setting the troop count
    p1->setTroopCount(5, country_a);
    p2->setTroopCount(1, country_b);
    
    p1->setTroopCount(6, country_c);
    p2->setTroopCount(7, country_d);
    p1->setTroopCount(8, country_e);
    p2->setTroopCount(9, country_f);
    
    // Adding adjacent countries
    country_a->addCountry(country_b);
    country_b->addCountry(country_a);
    
    country_c->addCountry(country_d);
    country_d->addCountry(country_c);
    country_e->addCountry(country_f);
    country_f->addCountry(country_e);
    
    //cout <<  country_a->getTroopCount() << endl;
    
    //p1->setTroopCount(100, country_a);
    //cout <<  p1->getTroopCount(country_a) << endl;
 
    p1->attack();
    
    cout << " " << endl;
    cout << "-----------" << endl;
    
    cout << "Armies in country a: " << country_a->getTroopCount() << endl;
    cout << "Armies in country a: " << country_b->getTroopCount() << endl;
    
    // Deleting and setting player objects to null
    delete p1;
    delete p2;
    p1 = NULL;
    p2 = NULL;

    
    // Player-2
    /*
    p2.collectionOfCountries();
    p2.diceObject();
     p1.addCards(card5);
     p1.addCards(card4);
     p1.addCards(card1);
     p1.addCards(card2);
     p1.addCards(card3);
    
     Card * card5 = new Card(INFANTRY);
     Card * card4 = new Card(ARTILLERY);
     Card * card3 = new Card(ARTILLERY);
     Card * card1 = new Card(INFANTRY);
     Card * card2 = new Card(CAVALRY);*/
    /*
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    delete hh;
   hh = NULL;
    
    
    
    
    
    
    
    
    
    cout <<  p1.getName() << endl;
    
    p1.setName(hh);
    
    string *hh = new string("ANik");
    
     
    cout << "Done" << endl;
     */
     //p1.collectionOfRiskCards();
}


