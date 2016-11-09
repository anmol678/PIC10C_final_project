//cards.h

#include <string>
#include <vector>

#ifndef CARDS_H
#define CARDS_H

enum suit_t {CLUBS, DIAMONDS, HEARTS, SPADES};
enum rank_t {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 12, QUEEN = 13, KING = 14};

class Card {
public:
    //Constructor assigns random rank & suit to card.
    Card();
    
    //Accessors
    //Returns a string with the suit of the card
    std::string get_suit() const;
    //Returns a string with the rank of the card
    std::string get_rankName() const;
    
    //Converts card rank to number.
    //The possible returns are: 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10
    int get_rank() const;
    
    //Converts card rank to value.
    //The possible returns are: 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10
    int get_value() const;
    
    //Compare rank of two cards. E.g: Eight<Jack is true.
    //Assume Ace is always 11.
    //Useful if you want to sort the cards.
    bool operator < (Card card2) const;
    
private:
    suit_t suit;
    rank_t rank;
};

#endif