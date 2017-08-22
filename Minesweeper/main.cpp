/** Main file for Minesweeper
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 10/8/2017
 */

#include <iostream> //std::cin and std::cout;
#include "ClassBoard.h"

using namespace std;

/** Function getStartingCommand
 * Asks and retrieves the user if they would like the start a new game or load a saved game
 * Returns a letter corresponding to the user's response
 */
char getStartingCommand()
{
	char response;
	cout << "Welcome to Minesweeper\n";
	while (true)
	{
		cout << "Would you like to start a (n)ew game or (l)oad an existing game? ";
		cin >> response;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //flush the cin buffer
		response = tolower(response);
		if (response == 'n' || response == 'l')
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function getDifficulty
 * Asks and retrieves the user's difficulty for the game
 * Returns a letter corresponding to the difficulty the user has selected
 */
char getDifficulty()
{
	char response;
	while (true)
	{
		cout << "What difficulty would you like? (e)asy, (m)edium, (h)ard, (c)ustom: ";
		cin >> response;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		response = tolower(response);
		if (response == 'e' || response == 'm' || response == 'h' || response == 'c')
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function getBoardWidth
 * Asks the user for the width of the board
 * Returns the width of the board as an integer
 */
int getBoardWidth()
{
	int response;
	while (true)
	{
		cout << "Enter the width of the board (9 - 26): ";
		cin >> response;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (response >= 9 && response <= 26)
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function getBoardHeight
 * Asks the user for the height of the board
 * Returns the height of the board as an integer
 */
int getBoardHeight()
{
	int response;
	while (true)
	{
		cout << "Enter the height of the board (9 - 24): ";
		cin >> response;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (response >= 9 && response <= 24)
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function getMaxBombs
 * Asks the user for the number of bombs on the board
 * Returns the number of bombs as an integer
 */
int getMaxBombs(int boardWidth, int boardHeight)
{
	int response;
	int max = boardWidth * boardHeight - boardWidth - boardHeight + 1;
	while (true)
	{
		cout << "Enter number of bombs (10 - " << max << "): ";
		cin >> response;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (response >= 10 && response <= max)
		{
			return response;
		}
		cout << "Invalid command, please try again.\n";
	}
}

/** Function getCommand
 * Gets the user's command (reveal / mark / unmark) from cin
 * Returns the correct command the user has entered as a char
 */
char getCommand()
{
	char response;
	while (true)
	{
		cout << "What would you like to do? (r)eveal or (m)ark? or (u)nmark or (s)ave? ";
		cin >> response;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		response = tolower(response);
		if (response == 'r' || response == 'm' || response == 'u' || 's')
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
	char responseChar;
	while (true)
	{
		cout << "Enter the x-coordinate: ";
		cin >> responseChar;
		responseChar = toupper(responseChar);
		response = responseChar - 65;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
	char xCoordChar = xCoord + 65;
	while (true)
	{
		switch (command)
		{
			case 'r':
			{
				cout << "Reveal " << xCoordChar << yCoord << "? (y/n) ";
				break;
			}
			case 'm':
			{
				cout << "Mark " << xCoordChar  << yCoord << " as a bomb? (y/n) ";
				break;
			}
			case 'u':
			{
				cout << "Unmark " << xCoordChar << yCoord << "? (y/n) ";
				break;
			}
		}
		char response;
		cin >> response;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
				if (theBoard.getNonBombsLeft() == theBoard.getBoardWidth() * theBoard.getBoardHeight() - theBoard.getMaxBombs())
				{
					theBoard.initialiseBoard(xCoord, yCoord);
				}
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
bool getAliveStatus(int xCoord, int yCoord, ClassBoard& theBoard)
{
	if (theBoard.getValue(xCoord, yCoord) == 9)
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
	if (theBoard.getNonBombsLeft() == 0)
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
	int boardWidth, boardHeight, maxBombs, xCoord, yCoord;
	char command, difficulty, response;
	bool alive = true, playerWins = false;
	string key = "minesweeper", hashkey = "hashkey";
	ClassBoard theBoard;
	response = getStartingCommand();
	if (response == 'n')
	{
		difficulty = getDifficulty();
		switch (difficulty)
		{
			case 'e':
			{
				boardWidth = 9;
				boardHeight = 9;
				maxBombs = 10;
				break;
			}
			case 'm':
			{
				boardWidth = 16;
				boardHeight = 16;
				maxBombs = 40;
				break;
			}
			case 'h':
			{
				boardWidth = 26;
				boardHeight = 16;
				maxBombs = 90;
				break;
			}
			case 'c':
			{
				boardWidth = getBoardWidth();
				boardHeight = getBoardHeight();
				maxBombs = getMaxBombs(boardWidth, boardHeight);
				break;
			}
		}
		theBoard.setBoardWidth(boardWidth);
		theBoard.setBoardHeight(boardHeight);
		theBoard.setMaxBombs(maxBombs);
		theBoard.setBombsLeft(maxBombs);
		theBoard.setNonBombsLeft(boardWidth * boardHeight - maxBombs);
		theBoard.makeBoard();
	}
	else if (response == 'l')
	{
		int temp = theBoard.load(key, hashkey);
		if (temp == 1)
		{
			cout << "Error accessing save file. Press enter to exit.";
			cin.get();
			return 0;
		}
		else if (temp == 2)
		{
			cout << "Save file corrupted. Press enter to exit.";
			cin.get();
			return 0;
		}
	}
	//main game loop
	while (alive && !playerWins)
	{
		theBoard.drawBoard();
		command = getCommand();
		if (command == 's')
		{
			response = NULL;
			while (response != 'y' && response != 'n')
			{
				cout << "Do you want to save and quit the game? (y/n) ";
				cin >> response;
				response = tolower(response);
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (response == 'y')
			{
				theBoard.save(key, hashkey);
				cout << "Game saved. Press enter to exit.";
				cin.get();
				return 0;
			}
		}
		else
		{
			xCoord = getXCoord(theBoard.getBoardWidth());
			yCoord = getYCoord(theBoard.getBoardHeight());
			if (confirmCommand(command, xCoord, yCoord))
			{
				if (executeCommand(command, xCoord, yCoord, theBoard) == 0) //if command was valid and gets executed
				{
					alive = getAliveStatus(xCoord, yCoord, theBoard);
					playerWins = getWinStatus(theBoard, theBoard.getMaxBombs());
				}
			}
		}
	}
	theBoard.drawBoard();
	if (playerWins)
	{
		cout << "Congratulations, you win!\n";
	}
	else if (!alive)
	{
		cout << "Game over!\n";
	}
	cout << "Press Enter to exit.";
	cin.get();
	return 0;
}