
#include "Cards.h"
#include "Map.h"

#include <cstdlib>
#include <ctime>

Country Card::getCountry() const {
	return country;
}

void Card::setCountry(const Country& country) {
	this->country = country;
}

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

Card Deck::draw(Player& player) {
	std::srand(std::time(0));
	int randIndex = std::rand() % cards.size();
	Card card = cards[randIndex];

	player.getHand().add(card);
	cards.erase(cards.begin() + randIndex);
	return card;
}

int Deck::nCards() const {
	return cards.size();
}

void Deck::loadDeck(const std::vector<Country>& countries) {
	for (int i = 0; i < countries.size(); ++i) {
		CardType cardType = CardType(i % 3);
		Country country = countries[i];
		cards.push_back(Card(country, cardType));
	}
}

int Deck::getNExchanges() {
	return nExchanges;
}

void Deck::incNExchanges() {
	++nExchanges;
}



int Hand::getArmies() {
	return Deck::getNExchanges() * 5;
}

std::vector<Card> Hand::getCards() const {
	return cards;
}

void Hand::add(const Card& card) {
	cards.push_back(card);
}

int Hand::exchange(const Card& card0, const Card& card1, const Card& card2) {
	if (card0.getCardType() == card1.getCardType() &&
		card1.getCardType() == card2.getCardType()) {
		Deck::incNExchanges();
		int armies = Hand::getArmies();
		return armies;
	}
	else if (card0.getCardType() != card1.getCardType() &&
		card1.getCardType() != card2.getCardType() &&
		card0.getCardType() != card2.getCardType()) {
		Deck::incNExchanges();
		int armies = Hand::getArmies();
		return armies;
	}
	return 0;
}