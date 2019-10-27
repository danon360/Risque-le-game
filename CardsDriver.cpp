
#include <iostream>
#include "Cards.h"

using namespace std;


int main()
{

	Deck* deck = new Deck();                   
	deck->loadDeck(42);                        //creating a deck of cards 

	cout << endl << "Cards in hands:" << endl << endl;

	Hand* hand = new Hand();                  // a pointer to a hand object

	auto p1 = CardType::INFANTRY;              
	auto *ptr1 = &p1;

	auto p2 = CardType::ARTILLERY;
	auto* ptr2 = &p2;

	auto p3 = CardType::CAVALRY;
	auto* ptr3 = &p3;

	auto p4 = CardType::INFANTRY;
	auto* ptr4 = &p4;

	auto p5 = CardType::INFANTRY;
	auto* ptr5 = &p5;
	                                             // creating cards 
	Card* card1 = new Card(ptr1);
	Card* card2 = new Card(ptr2);
	Card* card3 = new Card(ptr3);
	Card* card4 = new Card(ptr4);
	Card* card5 = new Card(ptr5);

	hand->add(card1);               // adding the cards created to the hand object
	hand->add(card2);
	hand->add(card3);
	hand->add(card4);
	hand->add(card5);


	hand->Display();
	cout << endl;

	hand->exchange();
	
	return 0;


}
