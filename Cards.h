#pragma once

#include "Map.h"
#include "Player.h"
#include <iostream>
#include <string>

enum CardType {
	INFANTRY, ARTILLERY, CAVALRY
};

class Card {
private:
	Country country;
	CardType cardType;

public:
	Card(const Country& country, CardType cardType) :
		country(country), cardType(cardType) {}

	Country getCountry() const;

	void setCountry(const Country& country);

	CardType getCardType() const;

	std::string getCardTypeAsString() const;

	void setCardType(CardType cardType);

	friend std::ostream& operator<<(std::ostream& os, const Card& card) {
		os << "country: " << card.country.getName() << ", type: ";
		switch (card.cardType) {
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
	std::vector<Card> cards;

	static int nExchanges;

public:
	Deck() = default;

	Deck(const std::vector<Card>& cards) : cards(cards) {}

	Card draw(Player& player);

	int nCards() const;

	void loadDeck(const std::vector<Country>& countries);

	static int getNExchanges();

	static void incNExchanges();
};

class Hand {
private:
	std::vector<Card> cards;

	static int getArmies();

public:
	Hand() = default;

	Hand(const std::vector<Card>& cards) : cards(cards) {}

	std::vector<Card> getCards() const;

	int size() const { return cards.size(); }

	bool empty() const { return cards.empty(); }

	void add(const Card& card);

	int exchange(const Card& card0, const Card& card1, const Card& card2);
};