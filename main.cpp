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
void print_player(std::ostream& out, Hand& player) {
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

//draws a new card for the given Hand from the given Deck and prints the new card
void draw_print(std::ostream& out, Hand& x, Deck& d) {
    x.drawCard(d);
    cout << "\nNew card:\n";
    x.printLast();
}

//returns true if the player goes bust (i.e. sum exceeds 21)
auto isBust = [](Hand hand){ return hand.sum() > 21;};

//returns true if the player's sum = 21
auto isBlackjack = [](Hand hand){return hand.sum() == 21;};

//dealer's turn is implemented by this function
void dealers_play(Hand& dealer, Deck d) {
    while (dealer.sum() < 17) {
        //The dealer continues to draw cards till the total value <= 17
        draw_print(cout, dealer, d);
        
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
    else if (bet == 0) {
        cout << "Place a valid bet.\n";
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

//accepts user input for what course of action to take
char hit_stand() {
    std::string choice;
    char ret;
    cout << "Do you want another card (hit/stand/double down)? ";
    cin >> choice;
    //After total value of cards is displayed the player is given a choice to draw another card
    
    if (choice == "hit" || choice == "y")
        ret = 'y';
    else if (choice == "stand" || choice == "n")
        ret = 'n';
    else if (choice == "double down" || choice == "dd")
        ret = 'd';
    else
        ret = hit_stand();
    
    return ret;
    //user choice is returned as char variable
}

//accepts input from user for the number of decks he wishes to play with
int num_decks() {
    int n = 0;
    cout << "\nEnter the number of decks you wish to play with: ";
    cin >> n;
    
    if (n == 0 || n > 8 || n < 0) {
        cout << "\nInvalid number of decks.";
        n = num_decks();
    }
    
    return n;
}

//essentially implements the aspect of the game that interacts and accepts various inputs from the player
bool engine(Deck& deck, Hand& dealer, Player& player, int& bet) {
    
    char choice = ' ';
    
    //Dealer's last card is revealed to the player
    cout << "\nDealer's card: \n";
    dealer.printLast();
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
            return false;
        }
        
        //If the player gets a blackjack he wins
        if (isBlackjack(player)) {
            cout << "\nBlackjack. You win " << bet << ".\n";
            player.updateMoney(bet);
            return false;
        }
        
    label:
        if (choice != 'n')
            choice = hit_stand();//Accepts players choice to hit or stand
        
        if (choice == 'n')
            return true;
        
        //If the player hits a card is drawn
        else if (choice == 'y') {
            draw_print(cout, player, deck);
        }
        
        //If the player chooses double down the bet is doubled and one last card is drawn
        else {
            //The player is asked to re-enter his choice if he does not have enough money to double down
            if (bet*2 > player.getMoney()) {
                cout << "\nYou don't have enough money to double down.\n";
                goto label;
            }
            
            //The bet is doubled, one last card is drawn and choice is set to 'n' to allow for the dealer's play to take place
            bet *= 2;
            draw_print(cout, player, deck);
            choice = 'n';
        }
    } while (choice == 'y' || choice == 'n');
    
    return false;
}

//the primary function for blackjack game
void blackjack() {
    //Player object initialized with amount 1000 and an empty Deck
    Deck temp(1);
    Player player(1000, temp);
    
    //Accepts the number of decks from the player
    int n = num_decks();
    do {
        std::srand(static_cast<int>(time(0)));
        
        //A new deck for the game is initialised, remember default deck has 4 deck worth of cards stored in it
        Deck deck(n);
        
        //Hand object for dealer is declared
        Hand dealer(deck);
        player = Player(player.getMoney(), deck);
        
        //player places the bet
        int bet = place_bet(player);
        
        //The game is carried out for the current deck, dealer and player
        bool flag = engine(deck, dealer, player, bet);
        
        if (flag) {
            print_dealer(cout, dealer);
            dealers_play(dealer, deck);
            
            //The total values of the dealer's hand and the player's hand are compared
            compare_sum(player, dealer, bet);
        }
        
        //The player cannot play anymore if he runs out of money
        if (player.getMoney() == 0) {
            cout << "\nYou have $0. GAME OVER!\nCome back when you have more money.\n\nBye!\n";
            break;
        }
        
        //The player cannot play anymore if the casino looses 900 or more
        else if (player.getMoney() >= 10000) {
            cout << "\nCongratulations. You beat the casino!\n\nBye!\n";
            break;
        }
        
        //If none of the above scenarios apply a new game begins
        else
            continue;
    } while (player.getMoney() > 0 && player.getMoney() < 10000);
    //This loop reiterates while the player hasn't lost all his money and the dealer hasn't lost $9000 or more
}

void sim_draw(Deck& deck, Hand& player) {
        draw_print(cout, player, deck);
        
        //If the player goes bust and has an ace, sum is recalculated with ace value set to 1
        if(player.hasAce() && isBust(player))
            player.changeAce();
        
        print_player(cout, player);
}

//dumb player implementation for simulation
bool dumb(Deck& deck, Player& player) {
    print_player(cout, player);
    
    while (player.sum() <= 17) {
        //The dumb player continues to draw cards till the total value <= 17
    label:
        sim_draw(deck, player);
    }
    
    //However for our dumb player to be truly dumb he should randomly draw a card even when the sum is >= 17
    
    if (isBust(player)) {
        cout << "Dumb player is bust\n";
        player.updateMoney(-1);
        return false;
    }
    
    if (isBlackjack(player)) {
        cout << "Dumb player blackjack\n";
        player.updateMoney(1);
        return false;
    }
    
    std::srand(static_cast<int>(time(0)));
    int r = rand() % 100;
    if (r%2 == 0)
        goto label;
    
    return true;
}

//smart player implementation for simulation
bool smart(Deck& deck, Player& player, Hand& dealer) {
    //If the player draws two aces, he is bust by default, sum is recalculated with one ace value set to 1
    if(player.hasAce() && isBust(player))
        player.changeAce();
    
    print_player(cout, player);
    
    //when the total value is 15 the highest card required for a blackjack is 6 (note that count is incremented for card with value 6 or less)
    while (player.sum() < 15 ) {
        //The smart player continues to draw cards till the total value < 15
    label:
        sim_draw(deck, player);
    }
    
    if (isBust(player)) {
        cout << "Smart player is bust\n";
        player.updateMoney(-1);
        return false;
    }
    
    if (isBlackjack(player)) {
        cout << "Smart player blackjack\n";
        player.updateMoney(1);
        return false;
    }
    
    int count = 0;//keeps count while counting cards
    dealer.cardCounting(count);
    player.cardCounting(count);
   // count /= deck.numDecks();
    
    //if count > 0 player has an advantage hence another card is drawn. however if count is equal to a small positive value and the sum is already very high the player might go bust.
    if ((count > 0 && player.sum() < 18) || count > 10)
        goto label;
    else if (count == 0 && player.sum() < 18) { //if the smart player is not at a clear advantage whether or not it withdraws a card is randomised
        /*std::srand(static_cast<int>(time(0)));
        int r = rand() % 100;
        
        if (r%2 == 1)*/
            goto label;
    }
    //if count < 0 dealer has advantage hence player does not draw another card
    else
        return true;
    
    return true;
}

int main() {
    Deck temp(1);
    Player player(10, temp);
    
    //Accepts the number of decks from the player
   // int n = num_decks();
    int num = 0;
    
    cout << "Enter 1 for dumb player and 0 for smart player: ";
    cin >> num;
    
    for(int i = 0 ; i < 10; ++i){
        Deck deck;
        Hand dealer(deck);
        player = Player(player.getMoney(), deck);
        
        bool flag = false;
        if (num == 0)
            flag = smart(deck, player, dealer);
        else
            flag = dumb(deck, player);
        
        if (flag) {
            print_dealer(cout, dealer);
            dealers_play(dealer, deck);
            int bet = 1;
            compare_sum(player, dealer, bet);
        }
    }
    
    cout << "\n" << player.getMoney();
}