#include "cards.h"
#include "hand.h"
#include "player.h"
#include "deck.h"
/*
 #include "cards.cpp"
 #include "hand.cpp"
 #include "player.cpp"
 #include "deck.cpp"
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;

//prints information about the player's hand to the console
void print_player(std::ostream& out, Player& player) {
    out << "\nYour cards: \n";
    out << player;
    out << "Your total is " << player.sum() << ".\n";
}

//prints information about the dealer's hand to the console
void print_dealer(std::ostream& out, Hand& dealer) {
    out << "\nDealer's cards: \n";
    out << dealer;
    out << "The dealer's total is " << dealer.sum() << ".\n";
}

//returns true if the player goes bust (i.e. sum exceeds 21)
bool isBust(Hand& hand) {
    if (hand.sum() > 21)
        return true;
    return false;
}

//returns true if the player's sum = 21
bool isBlackjack(Hand& hand) {
    if (hand.sum() == 21)
        return true;
    return false;
}

//dealer's turn is implemented by this function
void dealers_play(Hand& dealer, Deck d) {
    while (dealer.sum() < 17) {
        //The dealer continues to draw cards till the total value <= 5.5
        dealer.drawCard(d);
        cout << "\nNew card:\n";
        dealer.printLast();//The new card drawn is displayed
        
        //If the dealer goes bust and has an ace, sum is recalculated with ace value set to 1
        if(dealer.hasAce() && isBust(dealer))
            dealer.changeAce();
        
        print_dealer(cout, dealer);
    }
}

//asks the user to place a bet
int place_bet(const Player& player) {
    int bet = 0;
    cout << "\nYou have $" << player.getMoney() << ". "
    << "Enter bet: ";
    cin >> bet;//The bet is input by the player
    
    //If the bet exceeds total money, the player is asked to re-enter the bet
    if (bet > player.getMoney()) {
        cout << "You don't have that much money. Please bet again.\n";
        bet = place_bet(player);
    }
    return bet;
}

//compares the final sum of hands of the player and the dealer
void compare_sum(Player& player, Hand& dealer, int& bet) {
    if (dealer.sum() > 21) {
        cout << "\nDealer is bust. You win " << bet << ".\n";
        player.updateMoney(bet);
    }
    
    //It's a tie if both the player and the dealer don't bust and the values are equal
    else if (player.sum() == dealer.sum()) {
        cout << "\nIt's a push.\n";
    }
    
    //If both the player and the dealer do not bust:
    else {
        
        //The player wins the bet if he closer to 21 than the dealer is
        if (dealer < player) {
            cout << "\nYou win " << bet << ".\n";
            player.updateMoney(bet);
        }
        
        //The player loses the bet if the dealer is closer to 21 than he is
        else {
            cout << "\nToo bad. You lose " << bet << ".\n";
            player.updateMoney(-bet);
        }
    }
}
char hit_stand() {
    std::string choice;
    char ret;
    cout << "Do you want another card (hit/stand/double down)? ";
    cin >> choice;
    //Total value of cards is displayed and the player is given a choice to draw another card
    
    if (choice == "hit" || choice == "y")
        ret = 'y';
    else if (choice == "stand" || choice == "n")
        ret = 'n';
    else if (choice == "double down" || choice == "dd")
        ret = 'd';
    else
        ret = hit_stand();
    
    return ret;
}

int main() {
    //Player object initialized with amount 100
    Deck temp;
    Player player = Player(100, temp);
    
    //Keeps track of the number of games played
    int count = 0;
    
    do {
        std::srand(static_cast<int>(time(0)));
        
        //Keeps track of the game number
        count ++;
        
        //A new deck for the game is initialised
        Deck deck = Deck();
        //Hand object for dealer is declared
        Hand handDealer(deck);
        //Player is re-intialized for a new game
        player = Player(player.getMoney(), deck);
        
        char choice = ' ';
        //Player places a bet
        int bet = place_bet(player);
        
        //Dealer's last card is revealed to the player
        cout << "\nDealer's card: \n";
        handDealer.printLast();
        
        do {
            //If the player goes bust and has an ace, sum is recalculated with ace value set to 1
            if (player.hasAce() && isBust(player))
                player.changeAce();
            
            //The player's cards are displayed
            print_player(cout, player);
            
            //If the player goes bust he loses
            if (isBust(player)) {
                cout << "\nYou are bust. You lose " << bet << ".\n";
                player.updateMoney(-bet);
                break;
            }
            
            //If the player gets a blackjack he wins
            if (isBlackjack(player)) {
                cout << "\nBlackjack. You win " << bet << ".\n";
                player.updateMoney(bet);
                break;
            }
            
            if (choice != 'n')
                choice = hit_stand();//Accepts players choice to hit or stand
            
            //If the player decides to stand the dealer's cards are displayed and dealer takes the game forward
            if (choice == 'n') {
                print_dealer(cout, handDealer);
                dealers_play(handDealer, deck);
                
                //The total values of the dealer's hand and the player's hand are compared
                compare_sum(player, handDealer, bet);
                break;
            }
            
            //If the player hits a card is drawn
            else if (choice == 'y') {
                player.drawCard(deck);
                cout << "\nNew card:\n";
                player.printLast();
            }
            
            //If the player chooses double down the bet is doubled and one last card is drawn
            else {
                bet *= 2;
                player.drawCard(deck);
                cout << "\nNew card:\n";
                player.printLast();
                choice = 'n';
            }
        } while (choice == 'y' || choice == 'n');//This loop iterates only if the player opts to draw another card, otherwise his turn is over
        
        //The player cannot play anymore if he runs out of money
        if (player.getMoney() == 0) {
            cout << "\nYou have $0. GAME OVER!\nCome back when you have more money.\n\nBye!\n";
            break;
        }
        
        //The player cannot play anymore if the casino looses 900 or more
        else if (player.getMoney() >= 1000) {
            cout << "\nCongratulations. You beat the casino!\n\nBye!\n";
            break;
        }
        
        //If none of the above scenarios apply a new game begins
        else {
            continue;
        }
    } while (player.getMoney() > 0 && player.getMoney() < 1000); //This loop reiterates while the player hasn't lost all his money and the dealer hasn't lost 900 or more
    
    return 0;
}