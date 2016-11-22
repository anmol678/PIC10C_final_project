//cards.h

#include <string>
#include <vector>

#ifndef CARDS_H
#define CARDS_H

enum suit_t {CLUBS, DIAMONDS, HEARTS, SPADES};
enum rank_t {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

class Card {
public:
    Card();
    //Constructor assigns suit and rank based on s and r
    Card(int s, int r);
    
    //Accessors
    //Returns a string with the suit of the card
    std::string get_suit() const;
    //Returns a string with the rank of the card
    std::string get_rankName() const;
    //Converts Card rank to number.
    int get_rank() const;
    //Converts Card rank to value.
    int get_value() const;
    
    //Mutator
    //Changes value of Card as in case of Ace
    void set_value(int n);
    
    //Compare rank of two cards. E.g: Eight<Jack is true.
    //Assume Ace is always 11.
    bool operator < (Card card2) const;
    
    //overloading output operator for Card objects
    friend std::ostream& operator<<(std::ostream& out, const Card card);
private:
    suit_t suit;
    rank_t rank;
    int value;
};

#endif