#include "cards.h"
#include "hand.h"
#include "player.h"
#include "cards.cpp"
#include "hand.cpp"
#include "player.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;

//prints information about the player's hand to the console
void print_player(std::ostream& out, Player& player){
    out << "\nYour cards: \n";
    out << player;
    out << "Your total is " << player.sum() << ".\n";
}

//prints information about the dealer's hand to the console
void print_dealer(std::ostream& out, Hand& dealer){
    out << "\nDealer's cards: \n";
    out << dealer;
    out << "The dealer's total is " << dealer.sum() << ".\n";
}

void dealers_play(Hand& dealer){
    while (handDealer.sum() < 17){//The dealer continues to draw cards till the total value <= 5.5
        handDealer.drawCard();
        cout << "\nNew card:\n";
        handDealer.printLast();//The new card drawn is displayed

        print_dealer(cout, dealer);
}

//saves details about the game to the gamelog text file
void save_log(std::ofstream& fout, const int& count, const int& bet, Player& player, Hand& dealer){
    //General details about the game are added to the gamelog text file
    fout << "\n-----------------------------------------------\n";
    fout << "\nGame number: " << count << std::setw(20) << std::right << "Money left: $" << player.getMoney()
    << "\nBet: " << bet << "\n"; 

    //Details about player and dealer hands are added to the gamelog text file
    print_player(fout, player);           
    print_dealer(fout, dealer);
                    
}

int place_bet(const Player& player){
    cout << "\nYou have $" << player.getMoney() << ". "
    << "Enter bet: ";
    cin >> bet; //The bet is input by the player
        
    //If the bet exceeds total money, the player is asked to re-enter the bet
    if (bet > player.getMoney()){
        cout << "You don't have that much money. Please bet again.\n";
        place_bet(player);
    }
    return bet;
}

int main() {

    std::ofstream fout;
    fout.open("gamelog.txt"); //Creates gamelog.txt file
    
    Player player = Player(100); //Player object initialized with amount 100
    int count = 0; //Keeps track of the number of games played
    
    do {
        srand(static_cast<int>(time(0)));
        
        count ++;
      
        //Hand object for dealer is declared
        Hand handDealer = Hand();
        player = Player(player.getMoney());
    
        char choice;
        int bet = place_bet(player);
            do {
                //The player's cards are displayed
                print_player(cout, player);

                cout << "Do you want another card (y/n)? ";
                cin >> choice; //Total value of cards is displayed and the player is given a choice to draw another card
                
                //If the player declines to draw another card the dealer's cards are displayed and dealer takes the game forward. Subsequently, the total values of player's hand and dealer's hand are compared and it is decided if the player wins or loses the bet.
                if (choice == 'n') {
                    print_dealer(cout, handDealer);
                    dealers_play(handDealer);
                    
                    //the log for the game is stored in the gamelog text file
                    save_log(fout, count, bet, player, handDealer);

                    //The total values of the dealer's hand and the player's hand are compared
                    //The player loses the bet if he busts
                    if (player.sum() > 21) {
                        cout << "\nToo bad. You lose " << bet << ".\n";
                        player.updateMoney(-bet);
                    }
                    
                    //The player wins the bet if he doesn't bust but the dealer busts
                    else if (player.sum() <= 21 && handDealer.sum() > 21) {
                        cout << "\nYou win " << bet << ".\n";
                        player.updateMoney(bet);
                    }
                    
                    //It's a tie if both the player and the dealer don't bust and the values are equal
                    else if (player.sum() == handDealer.sum()) {
                        cout << "\nIts a tie.\n";
                    }
                    
                    //If both the player and the dealer do not bust:
                    else {
                        
                        //The player wins the bet if he closer to 21 than the dealer is
                        if (handDealer < player) {
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
                
                //If the player chooses to draw another card:
                else {
                    player.drawCard();
                    cout << "\nNew card:\n";
                    player.printLast();
                }
            } while (choice == 'y');//This loop iterates only if the player opts to draw another card. Otherwise, since the player's turn is over once the dealer draws his cards and values of the two hands are compared the game ends.
            
            //The player cannot play anymore if he runs out of money
            if (player.getMoney() == 0) {
                cout << "\nYou have $0. GAME OVER!\nCome back when you have more money.\n\nBye!\n";
                
                fout << "\n-----------------------------------------------";
                fout.close();
                
                break;
            }
            
            //The player cannot play anymore if the dealer looses 900 or more
            else if (player.getMoney() >= 1000) {
                cout << "\nCongratulations. You beat the casino!\n\nBye!\n";
                
                fout << "\n-----------------------------------------------";
                fout.close();
                
                break;
            }
            
            //If none of the above scenarios apply a new game begins
            else {
                continue;
            }
    } while (player.getMoney() > 0 && player.getMoney() < 1000); //This loop reiterates while the player hasn't lost all his money and the dealer hasn't lost 900 or more. Upon reiteration, new hands for both the player and the dealer are intialized and a new game begins.
    
    return 0;
}