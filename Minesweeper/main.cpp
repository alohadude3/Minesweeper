/** Main file for Minesweeper
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 10/8/2017
 */

#include <iostream>

using namespace std;

/** Function getCommand
 * Gets the user's command (reveal / mark / unmark) from cin
 */
char getCommand()
{
	char response;
	while (true)
	{
		cout << "What would you like to do? (r)eveal or (m)ark? or (u)nmark?\n";
		cin >> command;
		cin.clear();
		cin.sync();
		command = tolower(command);
		if (command == 'r' || command = 'm' || command = 'u')
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function getXCoord
 * Gets the user's xCoordinate from cin
 */
int getXCoord()
{
	int response;
	while (true)
	{
		cout << "Enter the x-coordinate: ";
		cin >> xCoord;
		cin.clear();
		cin.sync();
		if (xCoord >= 0 && xCoord < boardWidth)
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function getYCoord
 * Gets the user's yCoordinate from cin
 */
int getYCoord()
{
	int response;
	while (true)
	{
		cout << "Enter the y-coordinate: ";
		cin >> yCoord;
		cin.clear();
		cin.sync();
		if (yCoord >= 0 && yCoord < boardHeight)
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function confirmCommand
 * Asks the user for confirmation of their command
 */
char confirmCommand(char command, int xCoord, int yCoord)
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

/** Main function */
int main()
{
	//initialise variables
	int boardWidth = 10, boardHeight = 10, maxBombs = 20, xCoord, yCoord;
	char command;
	bool alive = true, commandConfirmed;
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
		xCoord = getXCoord();
		yCoord = getYCoord();
		commandConfirmed = confirmCommand(command, xCoord, yCoord);
	}
	system("pause");
	return 0;
}