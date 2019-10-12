#pragma once


#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

enum CardType {                                 //enum for the types of cards 
	INFANTRY, ARTILLERY, CAVALRY
};

class Card {
private:
	CardType* cardType;

public:
	Card(CardType* cardType) : cardType (cardType) {}

	CardType getCardType() const;

	std::string getCardTypeAsString() const;

	void setCardType(CardType cardType);

	friend std::ostream& operator<<(std::ostream& os,Card* card) {    //print the type as a string 
		os << " type: ";
		switch (card->getCardType()) {
		case INFANTRY:
			os << "infantry";
			break;
		case ARTILLERY:
			os << "artillerty";
			break;
		case CAVALRY:
			os << "cavalry";
			break;
		}
		return os;
	}

	
};

class Deck {
private:

	std::vector<Card*>* cards = new std::vector<Card*> ();  // deck is made of vector of cards 

	static int* nExchanges;

public:
	Deck() = default;

	Deck(std::vector<Card*>* cards) : cards(cards) {}

	Card* draw();

	int nCards() const;

	void loadDeck(int nbDeck);

	static int getNExchanges();

	static void incNExchanges();

};

class Hand {
private:

	std::vector<Card*>* cards;

	static int getArmies();


public:

	Hand();

	//Hand(std::vector<Card*>* cards) : cards(cards) {}

	std::vector<Card*>* getCards() const;

	int size() const { return cards->size(); }

	bool empty() const { return cards->empty(); }

	void add(Card* card);

	int exchange();

	void Display();

	bool AreThreeSame(Card* card_1, Card* card_2, Card* card_3);

	bool AreThreeDifferent(Card* card_1, Card* card_2, Card* card_3);


	

};