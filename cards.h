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
    
    //Converts card rank to number.
    //The possible returns are: 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10
    int get_rank() const;
    
    //Converts card rank to value.
    //The possible returns are: 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10
    int get_value() const;
    //Changes value of card as in case of Ace
    void set_value(int n);
    
    //Compare rank of two cards. E.g: Eight<Jack is true.
    //Assume Ace is always 11.
    //Useful if you want to sort the cards.
    bool operator < (Card card2) const;
    
private:
    suit_t suit;
    rank_t rank;
    int value;
};

#endif