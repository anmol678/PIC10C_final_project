//hand.cpp

#include "hand.h"
#include "cards.h"
#include "deck.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>

using std::cout;

//Default constructor initializes two random cards to the hand of cards
Hand::Hand(Deck& deck) {
    cards.push_back(deck.getCard());
    cards.push_back(deck.getCard());
}

//Accessor: Prints the last card stored in the hand of cards
void Hand::printLast() const {
    cout << cards[cards.size() - 1];
}

//Accessor: Finds the total value of all the cards in a hand
int Hand::sum() const {
    int sum = 0;

    class cal_sum {
    public:
        int operator()(int sum, Card x) const {
            return (sum += x.get_value());
        }
    };

    sum = std::accumulate(cards.begin(), cards.end(), 0, cal_sum());
    
    return sum;
}

//Accessor: Compares the values of two Hand objects and returns true if second hand has a higher total value
bool Hand::operator<(Hand hand2) const {
    return (sum() < hand2.sum());
}

//Accessor: Checks the if the hand has an ace
bool Hand::hasAce() const {
    for (auto it : cards)
        if(it.get_rankName() == "Ace")
            return true;
    return false;
}

//Mutator: Adds a card randomly generated from the deck to the hand
void Hand::drawCard(Deck& x) {
    cards.push_back(x.getCard());
}

//Mutator: Resets the hand for a new game
void Hand::resetHand() {
    cards.resize(0);
}

//Mutator: Sorts the cards in the vector in ascending order based on rank
void Hand::sortHand() {
    std::sort(cards.begin(),cards.end());
}

//Mutator: Changes the value of Ace card
void Hand::changeAce() {
    for (auto& it : cards)
        if(it.get_rankName() == "Ace" && it.get_value() == 11){
            it.set_value(1);
            return;
        }
}

//Output operator overloaded for Hand objects
std::ostream& operator<<(std::ostream& out, Hand& hand) {
    hand.sortHand();//The cards are sorted first
    
    for (auto it : hand.cards)
        out << it;
    
    return out;
}