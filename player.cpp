 //player.cpp

#include "player.h"
#include "hand.h"
#include "cards.h"

//Default constructor intializes m amount of money
Player::Player(int m) {
    money = m;
}

//Accessor: Returns the amount of money
int Player::getMoney() const {
    return money;
}

//Accessor: Updates money player has based on bets won or lost
void Player::updateMoney(int change) {
    money += change;
}
