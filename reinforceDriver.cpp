
#include <iostream>
#include "Player.h"


using namespace std;


int main()
{

	Player* player1 = new Player();

	auto p1 = CardType::INFANTRY;
	auto* ptr1 = &p1;

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


	player1->getHand()->add(card1);     // adding the cards created to the hand object
	player1->getHand()->add(card2);
	player1->getHand()->add(card3);
	player1->getHand()->add(card4);
	player1->getHand()->add(card5);

	player1->reinforce(player1);




}