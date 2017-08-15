/** Main file for Minesweeper
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 10/8/2017
 */

#include <iostream> //std::cin and std::cout;
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
				cout << "Reveal (" << xCoord << ", " << yCoord << ")? (y/n) ";
				break;
			}
			case 'm':
			{
				cout << "Mark (" << xCoord << ", " << yCoord << ") as a bomb? (y/n) ";
				break;
			}
			case 'u':
			{
				cout << "Unmark (" << xCoord << ", " << yCoord << ")? (y/n) ";
				break;
			}
		}
		char response;
		cin >> response;
		cin.clear();
		cin.sync();
		response = tolower(response);
		if (response == 'y')
		{
			return true;
		}
		else if (response == 'n')
		{
			return false;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function executeCommand
 * Executes the user entered command if it is valid
 * Returns 0 if the command is valid and is excuted, 1 otherwise
 */
int executeCommand(char command, int xCoord, int yCoord, ClassBoard& theBoard)
{
	if (xCoord >= 0 && xCoord < theBoard.getBoardWidth() && yCoord >= 0 && yCoord < theBoard.getBoardHeight()) //boundary check
	{
		switch (command)
		{
			case 'r':
			{
				return theBoard.revealGrid(xCoord, yCoord);
			}
			case 'm':
			{
				return theBoard.markGrid(xCoord, yCoord);
			}
			case 'u':
			{
				return theBoard.unmarkGrid(xCoord, yCoord);
			}
		}
	}
	return 1;
}

/** Function getAliveStatus
 * Checks to see if the last user entered command revealed a bomb
 * Returns true if the command didn't reveal a bomb, false otherwise
 */
bool getAliveStatus(char command, int xCoord, int yCoord, ClassBoard& theBoard)
{
	if (command == 'm' && theBoard.getChar(xCoord, yCoord) == 'B')
	{
		return false;
	}
	else
	{
		return true;
	}
}

/** Function getWinStatus
 * Checks the state of the game board to see if the player has won
 * Returns true if the player has won, false otherwise
 */
bool getWinStatus(ClassBoard& theBoard, int maxBombs)
{
	if (theBoard.getNonBombsLeft() == 0 || (theBoard.getMarkingsCount() == maxBombs && theBoard.getBombsLeft() == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/** Main function */
int main()
{
	//initialise variables
	int boardWidth = 10, boardHeight = 10, maxBombs = 20, xCoord, yCoord;
	char command;
	bool alive = true, playerWins = false;
	ClassBoard theBoard(boardWidth, boardHeight, maxBombs);
	theBoard.initialiseBoard();
	//main game loop
	while (alive && !playerWins)
	{
		system("cls"); //clear the terminal so the board can be redrawn
		cout << "Welcome to Minesweeper\n\n";
		cout << "There are " << theBoard.getBombsLeft() << " bombs remaining\n\n";
		theBoard.drawBoard();
		command = getCommand();
		xCoord = getXCoord(boardWidth);
		yCoord = getYCoord(boardHeight);
		if (confirmCommand(command, xCoord, yCoord))
		{
			executeCommand(command, xCoord, yCoord, theBoard);
			alive = getAliveStatus(command, xCoord, yCoord, theBoard);
			playerWins = getWinStatus(theBoard, maxBombs);
		}
	}
	system("pause");
	return 0;
}