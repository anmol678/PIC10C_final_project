//hand.h

#include <string>
#include <vector>
#include <iostream>
#include "cards.h"

#ifndef HAND_H
#define HAND_H

class Hand {
public:
    //Constructor
    //Initializes hand of cards with two random cards
    Hand();
    
    //Accessors
    //Prints the last card stored in the vector of cards
    void printLast() const;
    //Finds the total value of all the cards in a hand
    double sum() const;
    //Compares the values of two Hand objects
    bool operator < (Hand hand2) const;
    
    //Mutators
    //Adds a randomly generated card to the hand
    void drawCard();
    //Resets the hand for a new game
    void resetHand();
    //Sorts the cards in the vector in ascending order based on rank
    void sortHand();
    //Splits a hand into two if two initial cards are identical
    void split();
    
    //overloading output operator for Hand objects
    friend std::ostream& operator<<(std::ostream& out, Hand& hand);
private:
    //A vector of Cards
    std::vector<Card> cards;
};

#endif