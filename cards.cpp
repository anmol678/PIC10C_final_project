//cards.cpp

#include "cards.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>

Card::Card() {
}

//Constructor for the Card class.
Card::Card(int s, int r) {
    switch (s) {
        case 1: suit = CLUBS;
            break;
        case 2: suit = DIAMONDS;
            break;
        case 3: suit = HEARTS;
            break;
        case 4: suit = SPADES;
            break;
        default: break;
    }
    
    switch (r) {
        case  1: rank = ACE;
            break;
        case  2: rank = TWO;
            break;
        case  3: rank = THREE;
            break;
        case  4: rank = FOUR;
            break;
        case  5: rank = FIVE;
            break;
        case  6: rank = SIX;
            break;
        case  7: rank = SEVEN;
            break;
        case  8: rank = EIGHT;
            break;
        case  9: rank = NINE;
            break;
        case 10: rank = TEN;
            break;
        case  11: rank = JACK;
            break;
        case  12: rank = QUEEN;
            break;
        case  13: rank = KING;
            break;
        default: break;
    }
    
    if (get_rankName() == "Ace")
        value = 11;
    else
        value = get_rank();
}

//Accessor: returns a string with the suit of the card
std::string Card::get_suit() const {
    std::string suitName;
    switch (suit) {
        case CLUBS:
            suitName = "clubs";
            break;
        case DIAMONDS:
            suitName = "diamonds";
            break;
        case HEARTS:
            suitName = "hearts";
            break;
        case SPADES:
            suitName = "spades";
            break;
        default: break;
    }
    return suitName;
}

//Accessor: returns a string with the rank of the card
std::string Card::get_rankName() const {
    std::string rankName;
    switch (rank) {
        case ACE:
            rankName = "Ace";
            break;
        case TWO:
            rankName = "Two";
            break;
        case THREE:
            rankName = "Three";
            break;
        case FOUR:
            rankName = "Four";
            break;
        case FIVE:
            rankName = "Five";
            break;
        case SIX:
            rankName = "Six";
            break;
        case SEVEN:
            rankName = "Seven";
            break;
        case EIGHT:
            rankName = "Eight";
            break;
        case NINE:
            rankName = "Nine";
            break;
        case TEN:
            rankName = "Ten";
            break;
        case JACK:
            rankName = "Jack";
            break;
        case QUEEN:
            rankName = "Queen";
            break;
        case KING:
            rankName = "King";
            break;
        default: break;
    }
    return rankName;
}

//Accessor: Assigns a numerical value to card based on rank.
int Card::get_rank() const {
    if(static_cast<int>(rank) > 9 && static_cast<int>(rank) < 14)
        return 10;
    return static_cast<int>(rank) + 1 ;
}

//Accessor: Assigns value based on the rank of the card
int Card::get_value() const {
    return value;
}

//Mutator: Changes value assigned to card (required for Ace)
void Card::set_value(int n) {
    value = n;
}

//Accessor: Comparison operator for cards
//Returns TRUE if card1 < card2
bool Card::operator < (Card card2) const {
    return rank < card2.rank;
}