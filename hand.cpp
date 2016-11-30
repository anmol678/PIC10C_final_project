//hand.cpp

#include "hand.h"
#include "cards.h"
#include "deck.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using std::cout;

//Default constructor initializes two random cards from the given Deck to the Hand of cards
Hand::Hand(Deck& deck) {
    cards.push_back(deck.getCard());
    cards.push_back(deck.getCard());
}

//Accessor: Prints the last card stored in the Hand of cards
void Hand::printLast() const {
    cout << cards[cards.size() - 1];
}

//Accessor: Finds the sum of values of all cards in the Hand
int Hand::sum() const {
    int sum = 0;
    
    //function object to retrieve the value of a Card and add it to the sum
    class cal_sum {
    public:
        int operator()(int sum, Card x) const { return (sum += x.get_value()); }
    };
    
    //the functor cal_sum is called in the accumulate algorithm which collects the sum of the Hand for us
    sum = std::accumulate(cards.begin(), cards.end(), 0, cal_sum());
    
    return sum;
}

//Accessor: Compares the values of two Hand objects and returns true if second hand has a higher total value
bool Hand::operator<(Hand hand2) const {
    return (sum() < hand2.sum());
}

//Accessor: Checks if the hand has an Ace card
bool Hand::hasAce() const {
    //function object that checks the rank name of the Card object for Ace
    class val{
    public:
        bool operator()(Card x){return ("Ace" == x.get_rankName());}
    };
    
    //the functor is called in the find_if algorithm which essentially traverses through the vector and returns an iterator of the location where Ace was found
    if (find_if(cards.begin(), cards.end(), val()) != cards.end())
        return true;
    
        /*
        for (auto it : cards)
        if(it.get_rankName() == "Ace")
            return true;
         */
        
    return false;
}

//Accessor: Returns the number of cards in the vector of Cards
size_t Hand::length() const {
    return cards.size();
}

//Accessor: Card counting algorithm
void Hand::cardCounting(int& count) {
    for (auto& it : cards) {
        int val = it.get_value();
        if (val > 9 || val == 1)
            --count;
        else if (val > 6)
            continue;
        else
            ++count;
    }
}

//Mutator: Adds a card randomly generated from given the Deck to the hand
void Hand::drawCard(Deck& x) {
    cards.push_back(x.getCard());
}

//Mutator: Changes the value of Ace card
void Hand::changeAce() {
    //use of range based loops and auto keyword to iterate through the vector
    for (auto& it : cards)
        if(it.get_rankName() == "Ace" && it.get_value() == 11){
            it.set_value(1);
            return;
        }
}

//Output operator overloaded for Hand objects
std::ostream& operator<<(std::ostream& out, Hand& hand) {
    //a lambda function is employed to sort the Cards in the Hand in an increasing order of rank
    auto sortHand = [&](){ std::sort(hand.cards.begin(),hand.cards.end()); };
    sortHand();
    
    //for_each algorithm with a lambda function to print each Card stored in the vector of cards in the Hand object
    for_each (hand.cards.begin(), hand.cards.end(), [&](Card x){out << x;});
    //note that the output operator is overloaded for Card objects as well
    
    return out;
}