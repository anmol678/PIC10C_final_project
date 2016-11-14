//deck.h

#include "cards.h"

#ifndef DECK_H
#define DECK_H

class Deck {
public:
	//Default constructor intialises all 52 cards in the Deck
	Deck();

	//Returns a random card from the declk
	Card getCard();
	//Shuffles the deck
	void shuffle();

private:
	std::vector<Card> deck;
};

#endif