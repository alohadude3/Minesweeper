# FIT1048 Assignment 1
### Title: Minesweeper
### Author: Leo Huang
### Student ID: 16886294
### Due Date: Wednesday 23/08/2017

## Instructions
This Minesweeper is controlled by command line inputs.  
Most inputs will require a single character or number to be entered.  
Available commands will usually be hinted in brackets.  

For example:  

 `(e)asy, (m)edium, (h)ard  `

Enter the command `e` to select the easy difficulty.  

The game will conclude once one of the following two conditions are met:

* The player has revealed a bomb
* The player has revealed all cells that are not bombs

## Features
* Difficulty selection between 3 different presets or custom board
* Dynamic range for maximum number of bombs allowed based on custom board size
* Dynamic random generation of game board.
* Efficient storage of values of board.
* Ability to reveal, mark, and unmark cells
* Recursive revealing of all adjacent cells upon revealing a 0 cell
* Error handling for invalid commands
* Saving and loading the state of the game
* Encryption for the save file to prevent direct modifications

## To do
* Add a digital signature to the save file to make sure it's not corrupted
* Initialise the board only after the first cell has been revealed so it is not a bomb