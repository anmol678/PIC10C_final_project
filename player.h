//player.h

#include <string>
#include <vector>
#include "cards.h"
#include "hand.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Hand {
public:
    //Constructor
    //Assigns initial amount of money
    Player(int m);
    
    //Accessor
    //Returns money held by the player
    int getMoney() const;

    //Mutator
    //Modifies the amount held by the player based on bets won or lost
    void updateMoney(int bet);
    
private:
    int money;
};

#endif