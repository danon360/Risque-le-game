
#include "Cards.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


CardType Card::getCardType() const {
	return *cardType;
}

Card::~Card() {
	delete cardType;
	cardType = NULL;
}


void Card::setCardType(CardType cardType) {
	this->cardType = new CardType(cardType);
}
int* Deck::nExchanges = new int(0);

Card* Deck::draw() {          // here the player has to draw a card

	std::srand(time(0));                         // a random generator to choose a card to draw from the deck 
	int randIndex = std::rand() % cards->size();
	Card* card = cards->at(randIndex);

	Hand().add(card);                             // adding the card to the hand vector 
	cards->erase(cards->begin() + randIndex);       // removing the card from the deck vector
	return card;
}

int Deck::nCards() const {
	return cards->size();
}

Deck::~Deck() {

	if (cards != nullptr) {
		for (int i = 0; i < cards->size(); ++i)
			delete cards;
		cards = nullptr;
	}
}

void Deck::loadDeck(int nbDeck) {                  // creating each card and add it to the deck 
	for (int i = 0; i < nbDeck; ++i) {
		CardType* cardType = new CardType;
		*cardType = CardType(i % 3);
		cards->push_back(new Card (cardType));
	}
}

int Deck::getNExchanges() {
	return *nExchanges;
}

void Deck::incNExchanges() {
	++nExchanges;
}


int Hand::getArmies() {   // calculating the armies the player gets when he exchanges 

	static int* armies = new int(4);

	if (Deck::getNExchanges() < 6) {
		return *armies + 2;
	}
	
	return *armies + 5;
	
}

std::vector<Card*>* Hand::getCards() const {
	return cards;
}




void Hand::add(Card* card) {
	cards->push_back(card);
}


Hand::Hand() {
	cards = new vector<Card*>;
}
 
int Hand::exchange()
{
	int card_1, card_2, card_3;

	cout << "\nPick 3 cards to exchange" << endl             // ask the user to chose what cards he wants to exchange
			<< "Card# 1: ";
		cin >> card_1;
		cout << "Card# 2: ";
		cin >> card_2;
		cout << "Card# 3: ";
		cin >> card_3;
		cout << "\npicked card # " << card_1 << endl
			<< "picked card # " << card_2 << endl
			<< "picked card # " << card_3 << endl << endl;



	if
		(
			AreThreeSame(cards->at(card_1), cards->at(card_2), cards->at(card_3))   //checking if the cards are exchangable
			|| AreThreeDifferent(cards->at(card_1), cards->at(card_2), cards->at(card_3))
			) {


		vector<int> v{card_1, card_2, card_3};
		sort(v.begin(), v.end());



	    cards->erase(cards->begin() + v.at(v.size()-1) );       // removing the card from the hand vector
		cards->erase(cards->begin() + v.at(v.size()-2));
		cards->erase(cards->begin() + v.at(v.size()-3));
		
		cout << Hand::getArmies() << " Armies " << endl;
		return Hand::getArmies();

		Deck::incNExchanges();   // increment the number of exchanges each time a player exchanges

		

	}
	else cout << "these cards cannot be exchanged "<<endl; 
} 

bool Hand::AreThreeSame(Card* card_1, Card* card_2, Card* card_3)   // a method to check if the 3 cards are the same
{
	return
		(
			card_1->getCardType() == card_2->getCardType() &&
			card_2->getCardType() == card_3->getCardType() &&
			card_1 != card_2 &&
			card_2 != card_3 &&
			card_1 != card_3 
			)
    ;

}

bool Hand::AreThreeDifferent(Card* card_1, Card* card_2, Card* card_3)  // a method to check that the 3 cards are from different types
{
	return
		(
			card_1->getCardType() != card_2->getCardType() &&
			card_2->getCardType() != card_3->getCardType() &&
			card_1->getCardType() != card_3->getCardType()
			);

	
}
void Hand::Display() {               // printing the cards 

	for (int i = 0; i < cards->size(); i++) {
		cout  << "card# " << i  << " " << cards->at(i) << "   "<<endl;
	}
}

