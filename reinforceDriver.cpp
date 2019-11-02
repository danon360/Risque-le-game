
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

	player1->getHand()->Display();

	Country* country_a = new Country("country_a", 1, 1, 1);
	Country* country_b = new Country("country_b", 2, 1, 1);
	Country* country_c = new Country("country_c", 3, 1, 1);
	Country* country_d = new Country("country_d", 4, 2, 2);
	Country* country_e = new Country("country_e", 5, 2, 2);
	Country* country_f = new Country("country_f", 6, 2, 3);

	player1->addCountries(country_a);
	player1->addCountries(country_b);
	player1->addCountries(country_c);
	player1->addCountries(country_d);
	player1->addCountries(country_e);
	player1->addCountries(country_f);

	player1->reinforce(player1);




}