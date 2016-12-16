# PIC10C_final_project

The following project implements a single player game of Blackjack against the computer alongside Smart and Dumb player simulations for the game. The simulations are helpful in replicating real life strategies and subsequent results on the blackjack table. In all there are three simulations that can be selected:
1. Dumb player simulation: in which a player with minimal strategy and maximum dumbness is simulated to play blackjack against the computer. The amount given to the player by default is 10.
2. Smart player simulation: in which a player with card counting capabilities makes intelligent moves in a single player game against the computer. The amount given to the player by default is 10.
3. Dumb and Smart player simulation: in which both the dumb and the smart players play one after the other essentially on the same table with the same deck. This simulation runs 100 games for 100 different player money amounts begining from 10 and incrementing 5 after each iteration. The simulation also creates a text file with a three column of values - the base money amount, dumb player's final money and smart player's final money. These values can be used to plot graphs and perform further analysis to conclude the differences in the two startegies implemented.
*the amount bet during the simulation is set to 0.5 of the total money the player has, by default.
