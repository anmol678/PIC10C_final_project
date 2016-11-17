//hand.h

#include "cards.h"
#include "deck.h"
#include <vector>
#include <iostream>

#ifndef HAND_H
#define HAND_H

class Hand {
public:
    //Constructor
    //Initializes hand of cards with two random cards from the deck
    Hand(Deck& deck);
    
    //Accessors
    //Prints the last card stored in the vector of cards
    void printLast() const;
    //Finds the total value of all the cards in a hand
    int sum() const;
    //Compares the values of two Hand objects
    bool operator<(Hand hand2) const;
    //Checks the if the hand has an ace
    bool hasAce() const;
    
    //Mutators
    //Adds a card randomly generated from the deck to the hand
    void drawCard(Deck& x);
    //Resets the hand for a new game
    void resetHand();
    //Sorts the cards in the vector in ascending order based on rank
    void sortHand();
    //Flips the value of Ace
    void changeAce();
    
    //overloading output operator for Hand objects
    friend std::ostream& operator<<(std::ostream& out, Hand& hand);
private:
    //A vector of Cards
    std::vector<Card> cards;
};

#endif