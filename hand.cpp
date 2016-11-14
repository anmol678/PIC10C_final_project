//hand.cpp

#include "hand.h"
#include "cards.h"
#include "deck.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using std::cout;

//Default constructor initializes two random cards to the hand of cards
Hand::Hand() {
    cards.push_back(Card());
    cards.push_back(Card());
}

//Accessor: Prints the last card stored in the hand of cards
void Hand::printLast() const {
    int i = cards.size() - 1;
    cout << "\t" << std::setw(20) << std::left << cards[i].get_rankName()+" of "+cards[i].get_suit()+"\n";
}

//Accessor: Finds the total value of all the cards in a hand
int Hand::sum() const {
    int sum = 0.0;
    
    for (int i = 0; i < cards.size(); i++)
        sum += cards[i].get_value();

    return sum;
}

//Accessor: Compares the values of two Hand objects and returns true if second hand has a higher total value
bool Hand::operator<(Hand hand2) const {
    return sum() < hand2.sum();
}

//Accessor: Checks the if the hand has an ace
bool Hand::hasAce() const {
    for (int i = 0; i < cards.size(); i++)
        if(cards[i].get_rankName() == "Ace")
            return true;
    return false;    
}

//Mutator: Adds a card randomly generated from the deck to the hand
void Hand::drawCard(Deck x) {
    cards.push_back(x.getCard());
}

//Mutator: Resets the hand for a new game
void Hand::resetHand() {
    cards.resize(0);
}

//Mutator: Sorts the cards in the vector in ascending order based on rank
void Hand::sortHand() {
    sort(cards.begin(),cards.end());
}

//Mutator: Changes the value of Ace card
void Hand::changeAce() {
    for (int i = 0; i < cards.size(); i++)
        if(cards[i].get_rankName() == "Ace" && cards[i].get_value() == 11){
            cards[i].set_value(1);
            return;
        }
}

//Output operator overloaded for Hand objects
std::ostream& operator<<(std::ostream& out, Hand& hand) {
    hand.sortHand();//The cards are sorted first
    
    for (int i = 0; i < hand.cards.size(); i++)
        out << "\t" << std::setw(20) << std::left << hand.cards[i].get_rankName()+" of "+hand.cards[i].get_suit()+"\n";

    return out;
}