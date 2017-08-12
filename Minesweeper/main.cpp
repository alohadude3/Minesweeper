/** Main file for Minesweeper
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 10/8/2017
 */

#include <iostream>
#include "ClassBoard.h"

using namespace std;

/** Function getCommand
 * Gets the user's command (reveal / mark / unmark) from cin
 * Returns the correct command the user has entered as a char
 */
char getCommand()
{
	char response;
	while (true)
	{
		cout << "What would you like to do? (r)eveal or (m)ark? or (u)nmark?\n";
		cin >> response;
		cin.clear();
		cin.sync();
		response = tolower(response);
		if (response == 'r' || response == 'm' || response == 'u')
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function getXCoord
 * Gets the user's xCoordinate from cin
 * Returns the xCoordinate as an int
 */
int getXCoord(int boardWidth)
{
	int response;
	while (true)
	{
		cout << "Enter the x-coordinate: ";
		cin >> response;
		cin.clear();
		cin.sync();
		if (response >= 0 && response < boardWidth)
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function getYCoord
 * Gets the user's yCoordinate from cin
 * Returns the yCoordinate as an int
 */
int getYCoord(int boardHeight)
{
	int response;
	while (true)
	{
		cout << "Enter the y-coordinate: ";
		cin >> response;
		cin.clear();
		cin.sync();
		if (response >= 0 && response < boardHeight)
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function confirmCommand
 * Asks the user for confirmation of their command
 * Returns true of the user confirms, false otherwise
 */
bool confirmCommand(char command, int xCoord, int yCoord)
{
	while (true)
	{
		switch (command)
		{
			case 'r':
			{
				cout << "Reveal (" << xCoord << ", " << yCoord << ")? (y/n)";
				break;
			}
			case 'm':
			{
				cout << "Mark (" << xCoord << ", " << yCoord << ") as a bomb? (y/n)";
				break;
			}
			case 'u':
			{
				cout << "Unmark (" << xCoord << ", " << yCoord << ")? (y/n)";
				break;
			}
		}
		char response;
		cin >> response;
		cin.clear();
		cin.sync();
		if (response == 'y')
		{
			return true;
		}
		else if (response == 'x')
		{
			return false;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function validateCommand
 * Validates the user entered command
 * Returns true if the command can be operated on the board, false otherwise
 */
bool validateCommand(char command, int xCoord, int yCoord, ClassBoard& theBoard)
{

}

/** Main function */
int main()
{
	//initialise variables
	int boardWidth = 10, boardHeight = 10, maxBombs = 20, xCoord, yCoord;
	char command;
	bool alive = true, commandConfirmed, validCommand;
	ClassBoard theBoard(boardWidth, boardHeight, maxBombs);
	theBoard.initialiseBoard();
	//main game loop
	while (theBoard.getbombsLeft() > 0 && alive)
	{
		system("cls"); //clear the terminal so the board can be redrawn
		cout << "Welcome to Minesweeper\n\n";
		cout << "There are " << theBoard.getbombsLeft() << " bombs remaining\n\n";
		theBoard.drawBoard();
		command = getCommand();
		xCoord = getXCoord(boardWidth);
		yCoord = getYCoord(boardHeight);
		commandConfirmed = confirmCommand(command, xCoord, yCoord);
		if (commandConfirmed)
		{
			validCommand = validateCommand(command, xCoord, yCoord, theBoard);
		}
	}
	system("pause");
	return 0;
}