
#include "Cards.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using std::cin;

using std::cout;
using std::endl;
using std::string;
using std::vector;


CardType Card::getCardType() const {
	return *cardType;
}

std::string Card::getCardTypeAsString() const {       
	if (*cardType == INFANTRY) return "infantry";
	if (*cardType == ARTILLERY) return "artillery";
	if (*cardType == CAVALRY) return "cavalry";
}

void Card::setCardType(CardType cardType) {
	this->cardType = new CardType(cardType);
}
int* Deck::nExchanges = new int(0);

Card* Deck::draw() {

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

 /*Hand::Hand(std::vector<Card*>* cd) {

	cards = new vector<Card*> * (cd);
}*/
Hand::Hand() {
	cards = new vector<Card*>;
}
 


int Hand::exchange()
{
	int card_1, card_2, card_3;
	cout << "Pick 3 cards to exchange" << endl             // ask the user to chose what cards he wants to exchange
		<< "Card #1: ";
	cin >> card_1;
	cout << "Card #2: ";
	cin >> card_2;
	cout << "Card #3: ";
	cin >> card_3;
	cout << "picked card # " << card_1 << endl
		<< "picked card # " << card_2 << endl
		<< "picked card # " << card_3 << endl;

	if
		(
			AreThreeSame(cards->at(card_1), cards->at(card_2), cards->at(card_3))   //checking if the cards are exchangable
			|| AreThreeDifferent(cards->at(card_1), cards->at(card_2), cards->at(card_3))
			) {

		Deck::incNExchanges();   // increment the number of exchanges each time a player exchanges

		cout << Hand::getArmies() << " cards " << endl;
		return Hand::getArmies();
	}
	else cout << "these cards cannot be exchanged "<<endl; 
} 

bool Hand::AreThreeSame(Card* card_1, Card* card_2, Card* card_3)   // a method to check if the 3 cards are the same
{
	return
		(
			card_1->getCardType() == card_2->getCardType() &&
			card_2->getCardType() == card_3->getCardType()
			);

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

