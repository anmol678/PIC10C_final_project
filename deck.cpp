//deck.cpp

#include "deck.h"
#include "cards.h"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

//Constructor intialises all 52 cards in the Deck, takes in an integer value n to determine number of decks
Deck::Deck(int n) {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i < 5; i++)
            for (int j = 1; j < 14; j++)
                deck.push_back(Card(i, j));
}

//Mutator: A random card is returned from the deck
Card Deck::getCard() {
    shuffle();
    Card card = deck.back();
    deck.pop_back();
    return card;
}

//Mutator: Shuffles the deck
void Deck::shuffle() {
    std::srand(static_cast<int>(time(0)));
    std::random_shuffle(deck.begin(), deck.end());
    
    int i = rand() % deck.size();
    std::swap(deck[deck.size()-1], deck[i]);
}