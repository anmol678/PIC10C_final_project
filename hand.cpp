//hand.cpp

#include "hand.h"
#include "cards.h"
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
double Hand::sum() const {
    double sum = 0.0;
    
    for (int i = 0; i < cards.size(); i++)
        sum += cards[i].get_value();

    return sum;
}

//Accessor: Compares the values of two Hand objects and returns true if second hand has a higher total value
bool Hand::operator < (Hand hand2) const {
    return sum() < hand2.sum();
}

//Mutator: Adds a randomly generated card to the hand
void Hand::drawCard() {
    cards.push_back(Card());
}

//Mutator: Resets the hand for a new game
void Hand::resetHand() {
    cards.resize(0);
}

//Mutator: Sorts the cards in the vector in ascending order based on rank
void Hand::sortHand() {
    sort(cards.begin(),cards.end());
}

//Prints all the cards in the hand (stored in the vector of cards)
void Hand::print() {
    sortHand();//The cards are sorted first
    for (int i = 0; i < cards.size(); i++)
        cout << "\t" << std::setw(20) << std::left << cards[i].get_rankName()+" of "+cards[i].get_suit()+"\n";
}

//Writes all the cards in the hand in the log file
void Hand::printLog(std::ofstream& fout) {
    sortHand();//The cards are sorted first
    
    for (int i = 0; i < cards.size(); i++)
        fout << "\t" << std::setw(20) << std::left << cards[i].get_rankName()+" of "+cards[i].get_suit()+"\n";

}