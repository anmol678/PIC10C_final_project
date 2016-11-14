//deck.cpp

#include "deck.h"
#include "cards.h"
#include <cstdlib>
#include <algorithm>

//Default constructor intialises all 52 cards in the Deck
Deck::Deck() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 13; j++)
			deck.push_back(Card(i, j));
}

//A random card is returned from the deck
Card Deck::getCard() {
	shuffle();
	return deck.pop_back();
}

//Shuffles the deck
void Deck::shuffle() {
	std::random_shuffle(deck.begin(), deck.end());
}