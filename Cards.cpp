
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
	return cardType;
}

std::string Card::getCardTypeAsString() const {       
	if (cardType == INFANTRY) return "infantry";
	if (cardType == ARTILLERY) return "artillery";
	if (cardType == CAVALRY) return "cavalry";
}

void Card::setCardType(CardType cardType) {
	this->cardType = cardType;
}

int Deck::nExchanges = 0;

Card Deck::draw() {

	std::srand(time(0));                         // a random generator to choose a card to draw from the deck 
	int randIndex = std::rand() % cards.size();
	Card card = cards[randIndex];

	Hand().add(card);                             // adding the card to the hand vector 
	cards.erase(cards.begin() + randIndex);       // removing the card from the deck vector
	return card;
}

int Deck::nCards() const {
	return cards.size();
}

void Deck::loadDeck(int nbDeck) {                  // creating each card and add it to the deck 
	for (int i = 0; i < nbDeck; ++i) {
		CardType cardType = CardType(i % 3);
		cards.push_back(Card(cardType));
	}
}

int Deck::getNExchanges() {
	return nExchanges;
}

void Deck::incNExchanges() {
	++nExchanges;
}

/*void Deck::DisplayDeck() {

	for (int i = 0; i < cards.size(); i++) {
		cout << "card# " << i + 1 << cards.at(i) << "   " << endl;

	}
}*/



int Hand::getArmies() {

	static int armies = 4;

	if (Deck::getNExchanges() < 6) {
		return armies + 2;
	}
	else {
		return armies + 5;
	}
}

std::vector<Card> Hand::getCards() const {
	return cards;
}

void Hand::add(const Card& card) {
	cards.push_back(card);
}



int Hand::exchange()
{
	int card_1, card_2, card_3;
	cout << "Pick 3 cards to exchange" << endl
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
			AreThreeSame(cards.at(card_1), cards.at(card_2), cards.at(card_3))
			|| AreThreeDifferent(cards.at(card_1), cards.at(card_2), cards.at(card_3))
			) {

		Deck::incNExchanges();

		cout << Hand::getArmies() << " cards " << endl;
		return Hand::getArmies();
	}
	else cout << "these cards cannot be exchanged "<<endl; 
} 

bool Hand::AreThreeSame(Card card_1, Card card_2, Card card_3)
{
	return
		(
			card_1.getCardType() == card_2.getCardType() &&
			card_2.getCardType() == card_3.getCardType()
			);

	

}

bool Hand::AreThreeDifferent(Card card_1, Card card_2, Card card_3)
{
	return
		(
			card_1.getCardType() != card_2.getCardType() &&
			card_2.getCardType() != card_3.getCardType() &&
			card_1.getCardType() != card_3.getCardType()
			);

	
}
void Hand::Display() {

	for (int i = 0; i < cards.size(); i++) {
		cout  << "card# " << i  << " " << cards.at(i) << "   "<<endl;
	}
}

