//deck.h

#include "cards.h"
#include <vector>

#ifndef DECK_H
#define DECK_H

class Deck {
public:
    //Constructor intialises all 52 cards in the Deck, take in an integer value to determine number of decks
    Deck(int n = 4);//By default number of decks used for the game is 4, hence 4*52=208 cards are initialised in the Deck object
    
    //Mutators
    //Returns a random card from the declk
    Card getCard();
    //Shuffles the deck
    void shuffle();
    
private:
    std::vector<Card> deck;
};

#endif