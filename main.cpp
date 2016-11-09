#include "cards.h"
#include "hand.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;

int main() {

    std::ofstream fout;
    fout.open("gamelog.txt"); //Creates gamelog.txt file
    
    Player player = Player(100); //Player object initialized with amount 100
    int count = 0; //Keeps track of the number of games played
    do {
        //srand(static_cast<int>(time(0)));
        
        count ++;
      
        //Hand object for dealer is declared
        Hand handDealer = Hand();
        
        int money = player.getMoney();
        int bet = 0;
        char choice;
        
        cout << "\nYou have $" << money << ". "
        << "Enter bet: ";
        cin >> bet; //The bet is input by the player
        
        //If the bet exceeds total money, the player is asked to re-enter the bet
        if (bet > money) {
            cout << "You don't have that much money. Please bet again.\n";
        }
        
        else {
            fout << "\n-----------------------------------------------\n";
            
            fout << "\nGame number: " << count << std::setw(20) << std::right << "Money left: $" << player.getMoney()
            << "\nBet: " << bet << "\n"; //Certain details are written in the gamelog file
            
            do {
                cout << "\nYour cards:\n";
                player.print(); //The player's cards are displayed
                
                cout << "Your total is " << player.sum() << ". Do you want another card (y/n)? ";
                cin >> choice; //Total value of cards is displayed and the player is given a choice to draw another card
                
                //If the player declines to draw another card the dealer's cards are displayed and dealer takes the game forward. Subsequently, the total values of player's hand and dealer's hand are compared and it is decided if the player wins or loses the bet.
                if (choice == 'n') {
                    cout << "\nDealer's cards: \n";
                    handDealer.print();
                    cout << "The dealer's total is " << handDealer.sum() << ".\n";
                    
                    while (handDealer.sum() < 17){//The dealer continues to draw cards till the total value <= 5.5
                        handDealer.drawCard();
                        cout << "\nNew card:\n";
                        handDealer.printLast();//The new card drawn is displayed
                        
                        cout << "\nDealer's cards: \n";
                        handDealer.print();
                        cout << "The dealer's total is " << handDealer.sum() << ".\n";
                    }
                    
                    //Other details about the game are added to the gamelog file
                    fout << "\nYour cards:\n";
                    player.printLog(fout);
                    fout << "Your total: " << player.sum() << ".\n";
                    
                    fout << "\nDealer's cards: \n";
                    handDealer.printLog(fout);
                    fout << "Dealer's total is " << handDealer.sum() << ".\n";
                    
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
                        
                        //The player wins the bet if he closer to 7.5 than the dealer is
                        if (handDealer < player) {
                            cout << "\nYou win " << bet << ".\n";
                            player.updateMoney(bet);
                        }
                        
                        //The player loses the bet if the dealer is closer to 7.5 than he is
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
                cout << "\nYou have $0. GAME OVER!\nCome back when you have more money.\n\nBye!";
                
                fout << "\n-----------------------------------------------";
                fout.close();
                
                break;
            }
            
            //The player cannot play anymore if the dealer looses 900 or more
            else if (player.getMoney() >= 1000) {
                cout << "\nCongratulations. You beat the casino!\n\nBye!";
                
                fout << "\n-----------------------------------------------";
                fout.close();
                
                break;
            }
            
            //If none of the above scenarios apply a new game begins
            else {
                continue;
            }
        }
    } while (player.getMoney() > 0 && player.getMoney() < 1000); //This loop reiterates while the player hasn't lost all his money and the dealer hasn't lost 900 or more. Upon reiteration, new hands for both the player and the dealer are intialized and a new game begins.
    
    return 0;
}