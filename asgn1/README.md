Derick Pan
dpan7
Spring 2021
Lab1: Left, Right and Center - DESIGN.pdf

---------------------
DESCRIPTION

This C code implements a simple game called "Left, Right, and Center."
Between 1 and 14 players sit around a table with $3 in hand. There are three dice identical dices. 
3 sides of the dice are "PASS," 1 side of the die is "LEFT," 1 side of the die is "RIGHT," and the last is "CENTER." 
Each player takes a turn. If a player has $3, they roll three times. $2, roll two times. $1, roll one time. $0 you pass. 
If the die's face is "LEFT" they give the player a dollar on their left. If "RIGHT," dollar to the right. 
If "PASS," they pass. If "CENTER" they put a dollar into the pot in the center of the table. 
All players will keep playing until the only person with money left wins, taking all the pot money.

-------------------
FILES

-lrc.c
-philos.h
-Makefile
-README.md
-DESIGN.pdf



------------------
INSTRUCTIONS

To run this file, run the make command. Then type "./lrc" to run the program. 
Once the program runs, it'll ask for a seed (input an integer), and it'll ask for the number of players. 
Once both of those are entered, the program will show you the rounds they played and the winner's name, 
pot winnings, and bank money.

